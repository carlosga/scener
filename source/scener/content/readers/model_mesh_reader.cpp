// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/model_mesh_reader.hpp"

#include "scener/content/content_manager.hpp"
#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/content/gltf/constants.hpp"
#include "scener/graphics/effect_parameter.hpp"
#include "scener/graphics/effect_technique.hpp"
#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/igraphics_device_service.hpp"
#include "scener/graphics/index_buffer.hpp"
#include "scener/graphics/index_type.hpp"
#include "scener/graphics/model_mesh.hpp"
#include "scener/graphics/model_mesh_part.hpp"
#include "scener/graphics/service_container.hpp"
#include "scener/graphics/texture2d.hpp"
#include "scener/graphics/vertex_buffer.hpp"
#include "scener/graphics/vertex_declaration.hpp"
#include "scener/graphics/vulkan/buffer.hpp"

using nlohmann::json;
using scener::math::matrix4;
using scener::math::vector2;
using scener::math::vector3;
using scener::math::vector4;
using namespace scener::content::gltf;
using namespace scener::graphics;

namespace scener::content::readers
{
    auto content_type_reader<model_mesh>::read(content_reader* input, const std::string& key, const json& value) const noexcept
    {
        auto instance = std::make_shared<model_mesh>();

        instance->_name = key;
        instance->_mesh_parts.reserve(value[k_primitives].size());

        for (const auto& primitive : value[k_primitives])
        {
            instance->_mesh_parts.push_back(read_mesh_part(input, primitive));
        }

        return instance;
    }

    std::shared_ptr<model_mesh_part> content_type_reader<model_mesh>::read_mesh_part(content_reader* input, const json& value) const noexcept
    {
        auto instance      = std::make_shared<model_mesh_part>();
        auto gdservice     = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
        auto device        = gdservice->device();
        auto accessors     = std::vector<std::shared_ptr<gltf::accessor>>();
        auto elements      = std::vector<vertex_element>();
        auto vertex_stride = std::size_t { 0 };
        auto vertex_count  = std::size_t { 0 };
        auto indices       = input->read_object<gltf::accessor>(value[k_indices].get<std::string>());

        // Index buffer
        instance->_index_buffer = std::make_unique<index_buffer>(device, indices->attribute_count());
        instance->_index_buffer->set_data(indices->get_data());

        // Vertex buffer
        accessors.reserve(value[k_attributes].size());
        elements.reserve(value[k_attributes].size());

        // Vertex declaration
        for (auto it = value[k_attributes].begin(); it != value[k_attributes].end(); ++it)
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

        instance->_primitive_type  = static_cast<primitive_type>(value[k_mode].get<std::int32_t>());
        instance->_vertex_count    = vertex_count;
        instance->_start_index     = 0;
        instance->_vertex_offset   = 0;
        instance->_primitive_count = 0;
        instance->_vertex_buffer   = std::make_unique<vertex_buffer>(device, vertex_count, declaration);

        switch (instance->_primitive_type)
        {
        case primitive_type::line_list:
            instance->_primitive_count = (vertex_count / 2);
            break;
        case primitive_type::triangle_list:
            instance->_primitive_count = (vertex_count  / 3);
            break;
        case primitive_type::line_loop:
        case primitive_type::line_strip:
        case primitive_type::point_list:
        case primitive_type::triangle_fan:
        case primitive_type::triangle_strip:
            // TODO: Fix
            instance->_primitive_count = vertex_count;
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
        instance->_vertex_buffer->set_data({ data });

        // Effect Material
        const auto& materialref = value[k_material].get<std::string>();
        if (!materialref.empty())
        {
            instance->_effect = read_material(input, materialref);
        }

        return instance;
    }

    std::shared_ptr<effect_technique> content_type_reader<model_mesh>::read_material(content_reader*    input
                                                                                   , const std::string& key) const noexcept
    {
        const auto& material  = input->_root[k_materials][key];
        auto        technique = input->read_object_instance<effect_technique>(material[k_technique].get<std::string>());

        for (auto it = material[k_values].begin(); it != material[k_values].end(); ++it)
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
                default:
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
        default:
            throw std::runtime_error("unsupported attribute type");
        }
    }

    vertex_element_usage content_type_reader<model_mesh>::get_vertex_element_usage(const std::string& semantic) const noexcept
    {
        auto usage = vertex_element_usage::color;

        if (semantic == k_joint)
        {
            usage = vertex_element_usage::blend_indices;
        }
        else if (semantic == k_normal)
        {
            usage = vertex_element_usage::normal;
        }
        else if (semantic == k_position)
        {
            usage = vertex_element_usage::position;
        }
        else if (semantic == k_textbinormal)
        {
            usage = vertex_element_usage::binormal;
        }
        else if (semantic == k_textcoord_0)
        {
            usage = vertex_element_usage::texture_coordinate;
        }
        else if (semantic == k_texttangent)
        {
            usage = vertex_element_usage::tangent;
        }
        else if (semantic == k_weight)
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
