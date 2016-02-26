// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "ModelMeshReader.hpp"

#include <json11.hpp>

#include "scener/content/ContentManager.hpp"
#include "scener/content/ContentReader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/graphics/EffectParameter.hpp"
#include "scener/graphics/EffectTechnique.hpp"
#include "scener/graphics/IGraphicsDeviceService.hpp"
#include "scener/graphics/IndexBuffer.hpp"
#include "scener/graphics/Model.hpp"
#include "scener/graphics/ModelMesh.hpp"
#include "scener/graphics/ModelMeshPart.hpp"
#include "scener/graphics/RendererServiceContainer.hpp"
#include "scener/graphics/Texture2D.hpp"
#include "scener/graphics/VertexBuffer.hpp"
#include "scener/graphics/VertexDeclaration.hpp"
#include "scener/graphics/opengl/Buffer.hpp"
#include "scener/graphics/opengl/VertexArrayObject.hpp"

using json11::Json;
using scener::content::gltf::AttributeType;
using scener::math::matrix4;
using scener::math::vector2;
using scener::math::vector3;
using scener::math::vector4;
using scener::graphics::ComponentType;
using scener::graphics::EffectParameter;
using scener::graphics::EffectParameterClass;
using scener::graphics::EffectParameterType;
using scener::graphics::EffectTechnique;
using scener::graphics::IGraphicsDeviceService;
using scener::graphics::IndexBuffer;
using scener::graphics::Model;
using scener::graphics::ModelMesh;
using scener::graphics::ModelMeshPart;
using scener::graphics::PrimitiveType;
using scener::graphics::Texture2D;
using scener::graphics::VertexBuffer;
using scener::graphics::VertexDeclaration;
using scener::graphics::VertexElement;
using scener::graphics::VertexElementFormat;
using scener::graphics::VertexElementUsage;

namespace scener { namespace content { namespace readers {

auto ContentTypeReader<ModelMesh>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto        mesh       = std::make_shared<ModelMesh>();
    const auto& primitives = source["primitives"].array_items();

    mesh->_name = key;
    mesh->_mesh_parts.reserve(primitives.size());

    for (const auto& primitive : primitives)
    {
        mesh->_mesh_parts.push_back(read_mesh_part(input, primitive));
    }

    return mesh;
}

std::shared_ptr<ModelMeshPart> ContentTypeReader<ModelMesh>::read_mesh_part(ContentReader* input, const Json& source) const noexcept
{
    auto meshPart      = std::make_shared<ModelMeshPart>();
    auto gdService     = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
    auto device        = gdService->graphics_device();
    auto accessors     = std::vector<std::shared_ptr<gltf::accessor>>();
    auto elements      = std::vector<VertexElement>();
    auto vertexStride  = std::size_t { 0 };
    auto vertexCount   = std::size_t { 0 };
    auto indices       = input->read_object<gltf::accessor>(source["indices"].string_value());
    auto componentType = indices->component_type();
    auto indexCount    = indices->attribute_count();

    // Index buffer
    meshPart->_index_buffer = std::make_unique<IndexBuffer>(device, componentType, indexCount);
    meshPart->_index_buffer->set_data(indices->get_data());

    // Vertex buffer
    const auto& attributes = source["attributes"].object_items();

    accessors.reserve(attributes.size());
    elements.reserve(attributes.size());

    for (const auto& attribute : attributes)
    {
        const auto accessor   = input->read_object<gltf::accessor>(attribute.second.string_value());
        const auto format     = get_vertex_element_format(accessor->attribute_type());
        const auto usage      = get_vertex_element_usage(attribute.first);
        const auto usageIndex = static_cast<std::uint32_t>(usage);

        if (usage == VertexElementUsage::position)
        {
            vertexCount = accessor->attribute_count();
        }

        accessors.push_back(accessor);
        elements.push_back({ vertexStride, format, usage, usageIndex });

        vertexStride += accessor->byte_stride();
    }

    VertexDeclaration declaration(vertexStride, elements);

    meshPart->_primitive_type  = static_cast<PrimitiveType>(source["mode"].int_value());
    meshPart->_vertex_count    = vertexCount;
    meshPart->_start_index     = 0;
    meshPart->_vertex_offset   = 0;
    meshPart->_primitive_count = 0;
    meshPart->_vertex_buffer   = std::make_unique<VertexBuffer>(device, vertexCount, declaration);

    switch (meshPart->_primitive_type)
    {
    case PrimitiveType::line_list:
        meshPart->_primitive_count = (vertexCount / 2);
        break;
    case PrimitiveType::triangle_list:
        meshPart->_primitive_count = (vertexCount  / 3);
        break;
    case PrimitiveType::line_loop:
    case PrimitiveType::line_strip:
    case PrimitiveType::point_list:
    case PrimitiveType::triangle_fan:
    case PrimitiveType::triangle_strip:
        // TODO: Fix
        meshPart->_primitive_count = vertexCount;
        break;
    }

    // Build interleaved data array
    auto vertexData = std::vector<std::uint8_t>(vertexStride * vertexCount, 0);
    auto position   = vertexData.begin();

    for (std::size_t i = 0; i < vertexCount; ++i)
    {
        for (const auto& accessor : accessors)
        {
            const auto view = accessor->get_data(i, 1);

            std::copy_n(view.begin(), accessor->byte_stride(), position);

            position += static_cast<std::ptrdiff_t>(accessor->byte_stride());
        }
    }

    // Initialize vertex buffer
    meshPart->_vertex_buffer->set_data({ vertexData });

    // Effect Material
    const auto& materialRef = source["material"].string_value();
    if (!materialRef.empty())
    {
        meshPart->effect = read_material(input, materialRef);
    }

    return meshPart;
}

std::shared_ptr<EffectTechnique> ContentTypeReader<ModelMesh>::read_material(ContentReader*     input
                                                                           , const std::string& key) const noexcept
{
    const auto& material  = input->_root["materials"][key];
    const auto& values    = material["values"].object_items();
    auto        technique = input->read_object_instance<EffectTechnique>(material["technique"].string_value());

    for (const auto& value : values)
    {
        const auto& parameter  = technique->_parameters[value.first];
        const auto& paramValue = value.second;

        if (paramValue.is_null())
        {
            continue;
        }

        if (parameter->parameter_class() == EffectParameterClass::scalar)
        {
            switch (parameter->parameter_type())
            {
            case EffectParameterType::boolean:
                parameter->set_value<bool>(paramValue.bool_value());
                break;
            case EffectParameterType::byte:
                parameter->set_value<std::int8_t>(static_cast<std::int8_t>(paramValue.int_value()));
                break;
            case EffectParameterType::ubyte:
                parameter->set_value<std::uint8_t>(static_cast<std::uint8_t>(paramValue.int_value()));
                break;
            case EffectParameterType::int16:
                parameter->set_value<std::int16_t>(static_cast<std::int16_t>(paramValue.int_value()));
                break;
            case EffectParameterType::uint16:
                parameter->set_value<std::uint16_t>(static_cast<std::uint16_t>(paramValue.int_value()));
                break;
            case EffectParameterType::int32:
                parameter->set_value<std::int32_t>(static_cast<std::int32_t>(paramValue.int_value()));
                break;
            case EffectParameterType::uint32:
                parameter->set_value<std::uint32_t>(static_cast<std::uint32_t>(paramValue.int_value()));
                break;
            case EffectParameterType::single:
                parameter->set_value<float>(static_cast<float>(paramValue.number_value()));
                break;
            case EffectParameterType::string:
                parameter->set_value<std::string>(paramValue.string_value());
                break;

            case EffectParameterType::texture:
            case EffectParameterType::texture_1d:
            case EffectParameterType::texture_2d:
            case EffectParameterType::texture_3d:
            case EffectParameterType::texture_cube:
            case EffectParameterType::void_pointer:
                throw std::runtime_error("unknown parameter type");
            }
        }
        else if (parameter->parameter_class() == EffectParameterClass::vector)
        {
            switch (parameter->column_count())
            {
            case 2:
                parameter->set_value(input->convert<vector2>(paramValue.array_items()));
                break;
            case 3:
                parameter->set_value(input->convert<vector3>(paramValue.array_items()));
                break;
            case 4:
                parameter->set_value(input->convert<vector4>(paramValue.array_items()));
                break;
            }
        }
        else if (parameter->parameter_class() == EffectParameterClass::matrix)
        {
            parameter->set_value(input->convert<matrix4>(paramValue.array_items()));
        }
        else if (parameter->parameter_class() == EffectParameterClass::object)
        {
            technique->textures().push_back(input->read_object<Texture2D>(paramValue.string_value()));
        }
    }

    return technique;
}

VertexElementFormat ContentTypeReader<ModelMesh>::get_vertex_element_format(AttributeType type) const noexcept
{
    switch (type)
    {
    case AttributeType::vector2:
        return VertexElementFormat::vector2;
    case AttributeType::vector3:
        return VertexElementFormat::vector3;
    case AttributeType::vector4:
        return VertexElementFormat::vector4;
    case AttributeType::scalar:
        return VertexElementFormat::single;
    case AttributeType::matrix2:
    case AttributeType::matrix3:
    case AttributeType::matrix4:
        throw std::runtime_error("unsupported attribute type");
    }
}

VertexElementUsage ContentTypeReader<ModelMesh>::get_vertex_element_usage(const std::string& semantic) const noexcept
{
    VertexElementUsage usage = VertexElementUsage::color;

    if (semantic == "JOINT")
    {
        usage = VertexElementUsage::blend_indices;
    }
    else if (semantic == "NORMAL")
    {
        usage = VertexElementUsage::normal;
    }
    else if (semantic == "POSITION")
    {
        usage = VertexElementUsage::position;
    }
    else if (semantic == "TEXBINORMAL")
    {
        usage = VertexElementUsage::binormal;
    }
    else if (semantic == "TEXCOORD_0")
    {
        usage = VertexElementUsage::texture_coordinate;
    }
    else if (semantic == "TEXTANGENT")
    {
        usage = VertexElementUsage::tangent;
    }
    else if (semantic == "WEIGHT")
    {
        usage = VertexElementUsage::blend_weight;
    }
    else
    {
        throw std::runtime_error("unknown attribute [" + semantic + "]");
    }

    return usage;
}

}}}
