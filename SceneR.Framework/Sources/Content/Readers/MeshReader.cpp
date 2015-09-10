// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MeshReader.hpp>

#include <algorithm>
#include <iostream>

#include <Content/json11.hpp>
#include <Content/Readers/MaterialReader.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexDeclaration.hpp>
#include <System/Text/Encoding.hpp>

using json11::Json;
using SceneR::Graphics::Accessor;
using SceneR::Graphics::AttributeType;
using SceneR::Graphics::ComponentType;
using SceneR::Graphics::IndexBuffer;
using SceneR::Graphics::Model;
using SceneR::Graphics::ModelMesh;
using SceneR::Graphics::ModelMeshPart;
using SceneR::Graphics::PrimitiveType;
using SceneR::Graphics::VertexBuffer;
using SceneR::Graphics::VertexDeclaration;
using SceneR::Graphics::VertexElement;
using SceneR::Graphics::VertexElementFormat;
using SceneR::Graphics::VertexElementUsage;
using System::Text::Encoding;

namespace SceneR
{
    namespace Content
    {
        ContentTypeReader<ModelMesh>::ContentTypeReader()
        {
        }

        ContentTypeReader<ModelMesh>::~ContentTypeReader()
        {
        }

        std::shared_ptr<ModelMesh> ContentTypeReader<ModelMesh>::read(const std::pair<std::string, Json>& source
                                                                    , ContentReaderContext&               context)
        {
            auto mesh = std::make_shared<ModelMesh>();

            for (const auto& primitive : source.second["primitives"].array_items())
            {
                read_mesh_part(primitive, context, mesh);
            }

            mesh->_name = Encoding::convert(source.first);

            return mesh;
        }

        void ContentTypeReader<ModelMesh>::read_mesh_part(const json11::Json&        source
                                                        , ContentReaderContext&      context
                                                        , std::shared_ptr<ModelMesh> mesh) const
        {
            auto meshPart      = std::make_shared<ModelMeshPart>();
            auto accessors     = std::vector<std::shared_ptr<Accessor>>(12);
            auto elements      = std::vector<VertexElement>();
            auto vertexStride  = std::size_t(0);
            auto vertexCount   = std::size_t(0);
            auto indices       = context.find_object<Accessor>(source["indices"].string_value());
            auto componentType = indices->component_type();
            auto indexCount    = indices->attribute_count();
            auto indexData     = indices->get_data();
            auto material      = Encoding::convert(source["material"].string_value());

            // Index buffer
            meshPart->_index_buffer = std::make_unique<IndexBuffer>(context.graphics_device, componentType, indexCount);
            meshPart->_index_buffer->initialize();
            meshPart->_index_buffer->set_data(indexData.data());

            // Vertex buffer
            for (const auto& attribute : source["attributes"].object_items())
            {
                auto accessor   = context.find_object<Accessor>(attribute.second.string_value());
                auto format     = get_vertex_element_format(accessor->attribute_type());
                auto usage      = get_vertex_element_usage(attribute.first);
                auto usageIndex = static_cast<std::uint32_t>(usage);

                if (usage == VertexElementUsage::Position)
                {
                    vertexCount = accessor->attribute_count();
                }

                accessors[usageIndex] = accessor;
                elements.push_back({ vertexStride, format, usage, usageIndex });

                vertexStride += accessor->byte_stride();
            }

            // Remove empty slots from accessors vector
            auto items = std::remove_if(accessors.begin()
                                      , accessors.end()
                                      , [] (std::shared_ptr<Accessor> accessor) -> bool
                                        {
                                            return (accessor == nullptr);
                                        });

            accessors.erase(items);
            accessors.resize(source["attributes"].object_items().size());

            // Sort vertex elements based on usage index
            std::sort(elements.begin()
                    , elements.end()
                    , [] (const VertexElement& a, const VertexElement& b) -> bool
                      {
                          return (a.usage_index() < b.usage_index());
                      });

            auto declaration = std::make_unique<VertexDeclaration>(vertexStride, elements);

            meshPart->_vertex_buffer   = std::make_unique<VertexBuffer>(context.graphics_device, vertexCount, std::move(declaration));
            meshPart->_primitive_type  = static_cast<PrimitiveType>(source["primitive"].int_value());
            meshPart->_vertex_count    = vertexCount;
            meshPart->_start_index     = 0;
            meshPart->_vertex_offset   = 0;
            meshPart->_primitive_count = 0;

            switch (meshPart->_primitive_type)
            {
            case PrimitiveType::LineList:
                meshPart->_primitive_count = (vertexCount / 2);
                break;
            case PrimitiveType::TriangleList:
                meshPart->_primitive_count = (vertexCount  / 3);
                break;
            case PrimitiveType::LineLoop:
            case PrimitiveType::LineStrip:
            case PrimitiveType::PointList:
            case PrimitiveType::TriangleFan:
            case PrimitiveType::TriangleStrip:
                // TODO: Fix
                meshPart->_primitive_count = vertexCount;
                break;
            }

            // Build interleaved data array
            auto vertexData = std::vector<std::uint8_t>(vertexStride * vertexCount, 0);
            auto position   = vertexData.begin();

            for (std::size_t i = 0; i < vertexCount; i++)
            {
                for (auto accessor : accessors)
                {
                    accessor->get_data(i, 1, position);

                    position += accessor->byte_stride();
                }
            }

            // Initialize vertex buffer
            meshPart->_vertex_buffer->initialize();
            meshPart->_vertex_buffer->set_data(vertexData.data());

            // EffectMaterial
            // TODO: process material

            mesh->_mesh_parts.push_back(meshPart);
        }

        VertexElementFormat ContentTypeReader<ModelMesh>::get_vertex_element_format(const AttributeType& type) const
        {
            switch (type)
            {
            case AttributeType::Vector2:
                return VertexElementFormat::Vector2;
            case AttributeType::Vector3:
                return VertexElementFormat::Vector3;
            case AttributeType::Vector4:
                return VertexElementFormat::Vector4;
            case AttributeType::Scalar:
                return VertexElementFormat::Single;
            }
        }

        VertexElementUsage ContentTypeReader<ModelMesh>::get_vertex_element_usage(const std::string& semantic) const
        {
            VertexElementUsage usage = VertexElementUsage::Color;

            if (semantic == "JOINT")
            {
                usage = VertexElementUsage::BlendIndices;
            }
            else if (semantic == "NORMAL")
            {
                usage = VertexElementUsage::Normal;
            }
            else if (semantic == "POSITION")
            {
                usage = VertexElementUsage::Position;
            }
            else if (semantic == "TEXBINORMAL")
            {
                usage = VertexElementUsage::Binormal;
            }
            else if (semantic == "TEXCOORD_0")
            {
                usage = VertexElementUsage::TextureCoordinate;
            }
            else if (semantic == "TEXTANGENT")
            {
                usage = VertexElementUsage::Tangent;
            }
            else if (semantic == "WEIGHT")
            {
                usage = VertexElementUsage::BlendWeight;
            }
            else
            {
                std::cout << "unknown attribute [" << semantic << "]" << std::endl;
            }

            return usage;
        }
    }
}
