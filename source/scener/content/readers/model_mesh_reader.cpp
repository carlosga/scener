// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/model_mesh_reader.hpp"

#include <json11.hpp>

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

using json11::Json;
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

namespace scener { namespace content { namespace readers {

auto content_type_reader<model_mesh>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto        mesh       = std::make_shared<model_mesh>();
    const auto& primitives = source["primitives"].array_items();

    mesh->_name = key;
    mesh->_mesh_parts.reserve(primitives.size());

    for (const auto& primitive : primitives)
    {
        mesh->_mesh_parts.push_back(read_mesh_part(input, primitive));
    }

    return mesh;
}

std::shared_ptr<model_mesh_part> content_type_reader<model_mesh>::read_mesh_part(content_reader* input, const Json& source) const noexcept
{
    auto meshPart      = std::make_shared<model_mesh_part>();
    auto gdservice     = input->content_manager()->service_provider()->get_service<igraphics_device_service>();
    auto device        = gdservice->device();
    auto accessors     = std::vector<std::shared_ptr<gltf::accessor>>();
    auto elements      = std::vector<vertex_element>();
    auto vertexstride  = std::size_t { 0 };
    auto vertexcount   = std::size_t { 0 };
    auto indices       = input->read_object<gltf::accessor>(source["indices"].string_value());
    auto componenttype = indices->component_type();
    auto indexCount    = indices->attribute_count();

    // Index buffer
    meshPart->_index_buffer = std::make_unique<index_buffer>(device, componenttype, indexCount);
    meshPart->_index_buffer->set_data(indices->get_data());

    // Vertex buffer
    const auto& attributes = source["attributes"].object_items();

    accessors.reserve(attributes.size());
    elements.reserve(attributes.size());

    for (const auto& attribute : attributes)
    {
        const auto accessor = input->read_object<gltf::accessor>(attribute.second.string_value());
        const auto format   = get_vertex_element_format(accessor->attribute_type());
        const auto usage    = get_vertex_element_usage(attribute.first);
        const auto index    = static_cast<std::uint32_t>(usage);

        if (usage == vertex_element_usage::position)
        {
            vertexcount = accessor->attribute_count();
        }

        accessors.push_back(accessor);
        elements.push_back({ vertexstride, format, usage, index });

        vertexstride += accessor->byte_stride();
    }

    vertex_declaration declaration(vertexstride, elements);

    meshPart->_primitive_type  = static_cast<primitive_type>(source["mode"].int_value());
    meshPart->_vertex_count    = vertexcount;
    meshPart->_start_index     = 0;
    meshPart->_vertex_offset   = 0;
    meshPart->_primitive_count = 0;
    meshPart->_vertex_buffer   = std::make_unique<vertex_buffer>(device, vertexcount, declaration);

    switch (meshPart->_primitive_type)
    {
    case primitive_type::line_list:
        meshPart->_primitive_count = (vertexcount / 2);
        break;
    case primitive_type::triangle_list:
        meshPart->_primitive_count = (vertexcount  / 3);
        break;
    case primitive_type::line_loop:
    case primitive_type::line_strip:
    case primitive_type::point_list:
    case primitive_type::triangle_fan:
    case primitive_type::triangle_strip:
        // TODO: Fix
        meshPart->_primitive_count = vertexcount;
        break;
    }

    // Build interleaved data array
    auto data     = std::vector<std::uint8_t>(vertexstride * vertexcount, 0);
    auto position = data.begin();

    for (std::size_t i = 0; i < vertexcount; ++i)
    {
        for (const auto& accessor : accessors)
        {
            const auto view = accessor->get_data(i, 1);

            std::copy_n(view.begin(), accessor->byte_stride(), position);

            position += static_cast<std::ptrdiff_t>(accessor->byte_stride());
        }
    }

    // Initialize vertex buffer
    meshPart->_vertex_buffer->set_data({ data });

    // Effect Material
    const auto& materialref = source["material"].string_value();
    if (!materialref.empty())
    {
        meshPart->effect = read_material(input, materialref);
    }

    return meshPart;
}

std::shared_ptr<effect_technique> content_type_reader<model_mesh>::read_material(content_reader*   input
                                                                               , const std::string& key) const noexcept
{
    const auto& material  = input->_root["materials"][key];
    const auto& values    = material["values"].object_items();
    auto        technique = input->read_object_instance<effect_technique>(material["technique"].string_value());

    for (const auto& value : values)
    {
        const auto& parameter = technique->_parameters[value.first];
        const auto& pvalue    = value.second;

        if (pvalue.is_null())
        {
            continue;
        }

        if (parameter->parameter_class() == effect_parameter_class::scalar)
        {
            switch (parameter->parameter_type())
            {
            case effect_parameter_type::boolean:
                parameter->set_value<bool>(pvalue.bool_value());
                break;
            case effect_parameter_type::byte:
                parameter->set_value<std::int8_t>(static_cast<std::int8_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::ubyte:
                parameter->set_value<std::uint8_t>(static_cast<std::uint8_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::int16:
                parameter->set_value<std::int16_t>(static_cast<std::int16_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::uint16:
                parameter->set_value<std::uint16_t>(static_cast<std::uint16_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::int32:
                parameter->set_value<std::int32_t>(static_cast<std::int32_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::uint32:
                parameter->set_value<std::uint32_t>(static_cast<std::uint32_t>(pvalue.int_value()));
                break;
            case effect_parameter_type::single:
                parameter->set_value<float>(static_cast<float>(pvalue.number_value()));
                break;
            case effect_parameter_type::string:
                parameter->set_value<std::string>(pvalue.string_value());
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
                parameter->set_value(input->convert<vector2>(pvalue.array_items()));
                break;
            case 3:
                parameter->set_value(input->convert<vector3>(pvalue.array_items()));
                break;
            case 4:
                parameter->set_value(input->convert<vector4>(pvalue.array_items()));
                break;
            }
        }
        else if (parameter->parameter_class() == effect_parameter_class::matrix)
        {
            parameter->set_value(input->convert<matrix4>(pvalue.array_items()));
        }
        else if (parameter->parameter_class() == effect_parameter_class::object)
        {
            technique->textures().push_back(input->read_object<texture2d>(pvalue.string_value()));
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

}}}
