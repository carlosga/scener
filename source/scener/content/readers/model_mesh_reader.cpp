// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/model_mesh_reader.hpp"

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/graphics/effect_parameter.hpp"
#include "scener/graphics/effect_technique.hpp"
#include "scener/graphics/igraphics_device_service.hpp"
#include "scener/graphics/index_buffer.hpp"
#include "scener/graphics/model.hpp"
#include "scener/graphics/model_mesh.hpp"
#include "scener/graphics/model_mesh_part.hpp"
#include "scener/graphics/service_container.hpp"
#include "scener/graphics/texture2d.hpp"
#include "scener/graphics/vertex_buffer.hpp"
#include "scener/graphics/vertex_declaration.hpp"
#include "scener/graphics/opengl/buffer.hpp"
#include "scener/graphics/opengl/vertex_array_object.hpp"

using nlohmann::json;
using scener::content::gltf::attribute_type;
using scener::math::matrix4;
using scener::math::vector2;
using scener::math::vector3;
using scener::math::vector4;
using scener::graphics::component_type;
using scener::graphics::effect_parameter;
using scener::graphics::effect_parameter_class;
using scener::graphics::effect_parameter_type;
using scener::graphics::effect_technique;
using scener::graphics::igraphics_device_service;
using scener::graphics::index_buffer;
using scener::graphics::model;
using scener::graphics::model_mesh;
using scener::graphics::model_mesh_part;
using scener::graphics::primitive_type;
using scener::graphics::texture2d;
using scener::graphics::vertex_buffer;
using scener::graphics::vertex_declaration;
using scener::graphics::vertex_element;
using scener::graphics::vertex_element_format;
using scener::graphics::vertex_element_usage;

namespace scener::content::readers
{
    auto content_type_reader<model_mesh>::read(content_reader* input, const std::string& key, const json& source) const noexcept
    {
        auto mesh = std::make_shared<model_mesh>();

        mesh->_name = key;
        mesh->_mesh_parts.reserve(source["primitives"].size());

        for (const auto& primitive : source["primitives"])
        {
            mesh->_mesh_parts.push_back(read_mesh_part(input, primitive));
        }

        return mesh;
    }

    std::shared_ptr<model_mesh_part> content_type_reader<model_mesh>::read_mesh_part(content_reader* input, const json& source) const noexcept
    {
        auto mesh_part      = std::make_shared<model_mesh_part>();
        auto gdservice      = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
        auto device         = gdservice->device();
        auto accessors      = std::vector<std::shared_ptr<gltf::accessor>>();
        auto elements       = std::vector<vertex_element>();
        auto vertex_stride  = std::size_t { 0 };
        auto vertex_count   = std::size_t { 0 };
        auto indices        = input->read_object<gltf::accessor>(source["indices"].get<std::string>());
        auto component_type = indices->component_type();
        auto index_count    = indices->attribute_count();

        // Index buffer
        mesh_part->_index_buffer = std::make_unique<index_buffer>(device, component_type, index_count);
        mesh_part->_index_buffer->set_data(indices->get_data());

        // Vertex buffer
       accessors.reserve(source["attributes"].size());
        elements.reserve(source["attributes"].size());

        for (auto it = source["attributes"].begin(); it != source["attributes"].end(); ++it)
        {
            const auto accessor = input->read_object<gltf::accessor>(it.value().get<std::string>());
            const auto format   = get_vertex_element_format(accessor->attribute_type());
            const auto usage    = get_vertex_element_usage(it.key());
            const auto index    = static_cast<std::uint32_t>(usage);

            if (usage == vertex_element_usage::position)
            {
                vertex_count = accessor->attribute_count();
            }

            accessors.push_back(accessor);
            elements.push_back({ vertex_stride, format, usage, index });

            vertex_stride += accessor->byte_stride();
        }

        vertex_declaration declaration(vertex_stride, elements);

        mesh_part->_primitive_type  = static_cast<primitive_type>(source["mode"].get<std::int32_t>());
        mesh_part->_vertex_count    = vertex_count;
        mesh_part->_start_index     = 0;
        mesh_part->_vertex_offset   = 0;
        mesh_part->_primitive_count = 0;
        mesh_part->_vertex_buffer   = std::make_unique<vertex_buffer>(device, vertex_count, declaration);

        switch (mesh_part->_primitive_type)
        {
        case primitive_type::line_list:
            mesh_part->_primitive_count = (vertex_count / 2);
            break;
        case primitive_type::triangle_list:
            mesh_part->_primitive_count = (vertex_count  / 3);
            break;
        case primitive_type::line_loop:
        case primitive_type::line_strip:
        case primitive_type::point_list:
        case primitive_type::triangle_fan:
        case primitive_type::triangle_strip:
            // TODO: Fix
            mesh_part->_primitive_count = vertex_count;
            break;
        }

        // Build interleaved data array
        auto data     = std::vector<std::uint8_t>(vertex_stride * vertex_count, 0);
        auto position = data.begin();

        for (std::size_t i = 0; i < vertex_count; ++i)
        {
            for (const auto& accessor : accessors)
            {
                const auto view = accessor->get_data(i, 1);

                std::copy_n(view.begin(), accessor->byte_stride(), position);

                position += static_cast<std::ptrdiff_t>(accessor->byte_stride());
            }
        }

        // Initialize vertex buffer
        mesh_part->_vertex_buffer->set_data({ data });

        // Effect Material
        const auto& materialref = source["material"].get<std::string>();
        if (!materialref.empty())
        {
            mesh_part->effect = read_material(input, materialref);
        }

        return mesh_part;
    }

    std::shared_ptr<effect_technique> content_type_reader<model_mesh>::read_material(content_reader*   input
                                                                                   , const std::string& key) const noexcept
    {
        const auto& material  = input->_root["materials"][key];
        auto        technique = input->read_object_instance<effect_technique>(material["technique"].get<std::string>());

        for (auto it = material["values"].begin(); it != material["values"].end(); ++it)
        {
            const auto& parameter = technique->_parameters[it.key()];
            const auto& pvalue    = it.value();

            if (pvalue.is_null())
            {
                continue;
            }

            if (parameter->parameter_class() == effect_parameter_class::scalar)
            {
                switch (parameter->parameter_type())
                {
                case effect_parameter_type::boolean:
                    parameter->set_value<bool>(pvalue.get<bool>());
                    break;
                case effect_parameter_type::byte:
                    parameter->set_value<std::int8_t>(pvalue.get<std::int8_t>());
                    break;
                case effect_parameter_type::ubyte:
                    parameter->set_value<std::uint8_t>(pvalue.get<std::uint8_t>());
                    break;
                case effect_parameter_type::int16:
                    parameter->set_value<std::int16_t>(pvalue.get<std::int16_t>());
                    break;
                case effect_parameter_type::uint16:
                    parameter->set_value<std::uint16_t>(pvalue.get<std::uint16_t>());
                    break;
                case effect_parameter_type::int32:
                    parameter->set_value<std::int32_t>(pvalue.get<std::int32_t>());
                    break;
                case effect_parameter_type::uint32:
                    parameter->set_value<std::uint32_t>(pvalue.get<std::uint32_t>());
                    break;
                case effect_parameter_type::single:
                    parameter->set_value<float>(pvalue.get<float>());
                    break;
                case effect_parameter_type::string:
                    parameter->set_value<std::string>(pvalue.get<std::string>());
                    break;

                case effect_parameter_type::texture:
                case effect_parameter_type::texture_1d:
                case effect_parameter_type::texture_2d:
                case effect_parameter_type::texture_3d:
                case effect_parameter_type::texture_cube:
                case effect_parameter_type::void_pointer:
                    throw std::runtime_error("unknown parameter type");
                }
            }
            else if (parameter->parameter_class() == effect_parameter_class::vector)
            {
                switch (parameter->column_count())
                {
                case 2:
                    parameter->set_value(input->convert<vector2>(pvalue.get<json::array_t>()));
                    break;
                case 3:
                    parameter->set_value(input->convert<vector3>(pvalue.get<json::array_t>()));
                    break;
                case 4:
                    parameter->set_value(input->convert<vector4>(pvalue.get<json::array_t>()));
                    break;
                }
            }
            else if (parameter->parameter_class() == effect_parameter_class::matrix)
            {
                parameter->set_value(input->convert<matrix4>(pvalue.get<json::array_t>()));
            }
            else if (parameter->parameter_class() == effect_parameter_class::object)
            {
                technique->textures().push_back(input->read_object<texture2d>(pvalue.get<std::string>()));
            }
        }

        return technique;
    }

    vertex_element_format content_type_reader<model_mesh>::get_vertex_element_format(attribute_type type) const noexcept
    {
        switch (type)
        {
        case attribute_type::vector2:
            return vertex_element_format::vector2;
        case attribute_type::vector3:
            return vertex_element_format::vector3;
        case attribute_type::vector4:
            return vertex_element_format::vector4;
        case attribute_type::scalar:
            return vertex_element_format::single;
        case attribute_type::matrix2:
        case attribute_type::matrix3:
        case attribute_type::matrix4:
            throw std::runtime_error("unsupported attribute type");
        }
    }

    vertex_element_usage content_type_reader<model_mesh>::get_vertex_element_usage(const std::string& semantic) const noexcept
    {
        auto usage = vertex_element_usage::color;

        if (semantic == "JOINT")
        {
            usage = vertex_element_usage::blend_indices;
        }
        else if (semantic == "NORMAL")
        {
            usage = vertex_element_usage::normal;
        }
        else if (semantic == "POSITION")
        {
            usage = vertex_element_usage::position;
        }
        else if (semantic == "TEXBINORMAL")
        {
            usage = vertex_element_usage::binormal;
        }
        else if (semantic == "TEXCOORD_0")
        {
            usage = vertex_element_usage::texture_coordinate;
        }
        else if (semantic == "TEXTANGENT")
        {
            usage = vertex_element_usage::tangent;
        }
        else if (semantic == "WEIGHT")
        {
            usage = vertex_element_usage::blend_weight;
        }
        else
        {
            throw std::runtime_error("unknown attribute [" + semantic + "]");
        }

        return usage;
    }
}
