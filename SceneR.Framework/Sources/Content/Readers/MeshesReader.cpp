// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/MeshesReader.hpp>

#include <iostream>

#include <Content/json11.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/IndexElementSize.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexDeclaration.hpp>
#include <System/Text/Encoding.hpp>

using json11::Json;
using SceneR::Graphics::Accessor;
using SceneR::Graphics::AttributeType;
using SceneR::Graphics::IndexBuffer;
using SceneR::Graphics::IndexElementSize;
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
        MeshesReader::MeshesReader()
        {
        }

        MeshesReader::~MeshesReader()
        {
        }

        void MeshesReader::read(const Json& value, ContentReaderContext& context)
        {
            for (const auto& item : value["meshes"].object_items())
            {
                auto mesh = std::make_shared<ModelMesh>();

                for (const auto& source : item.second["primitives"].array_items())
                {
                    read_mesh_part(source, context, mesh);
                }

                mesh->_name = Encoding::convert(item.first);

                context.model->_meshes.push_back(mesh);
            }
        }

        void MeshesReader::read_mesh_part(const json11::Json&                          source
                                        , ContentReaderContext&                        context
                                        , std::shared_ptr<SceneR::Graphics::ModelMesh> mesh) const
        {
            auto meshPart     = std::make_shared<ModelMeshPart>();
            auto elemenSize   = IndexElementSize::SixteenBits;
            auto indices      = context.find_accessor(Encoding::convert(source["indices"].string_value()));
            auto indexCount   = indices->attribute_count();
            auto indexData    = indices->get_data();
            auto vertexStride = std::size_t(0);
            auto vertexCount  = std::size_t(0);
            auto usageIndex   = std::size_t(0);
            auto elements     = std::vector<VertexElement>();
            auto material     = Encoding::convert(source["material"].string_value());
            auto accessors    = std::vector<std::shared_ptr<Accessor>>(0);

            // Index buffer
            meshPart->_index_buffer = std::make_unique<IndexBuffer>(context.graphics_device, elemenSize, indexCount);

            meshPart->_index_buffer->initialize();
            meshPart->_index_buffer->set_data(indexData.data());

            // Vertex buffer
            for (const auto& attribute : source["attributes"].object_items())
            {
                auto name     = Encoding::convert(attribute.second.string_value());
                auto accessor = context.find_accessor(name);
                auto usage    = VertexElementUsage::Position;
                auto format   = VertexElementFormat::Vector3;

                switch (accessor->attribute_type())
                {
                case AttributeType::Vector2:
                    format = VertexElementFormat::Vector2;
                    break;
                case AttributeType::Vector3:
                    format = VertexElementFormat::Vector3;
                    break;
                case AttributeType::Vector4:
                    format = VertexElementFormat::Vector4;
                    break;
                case AttributeType::Scalar:
                    format = VertexElementFormat::Single;
                    break;
                }

                if (attribute.first == "JOINT")
                {
                    usage = VertexElementUsage::BlendIndices;
                }
                else if (attribute.first == "NORMAL")
                {
                    usage = VertexElementUsage::Normal;
                }
                else if (attribute.first == "POSITION")
                {
                    usage       = VertexElementUsage::Position;
                    vertexCount = accessor->attribute_count();
                }
                else if (attribute.first == "TEXBINORMAL")
                {
                    usage = VertexElementUsage::Binormal;
                }
                else if (attribute.first == "TEXCOORD_0")
                {
                    usage = VertexElementUsage::TextureCoordinate;
                }
                else if (attribute.first == "TEXTANGENT")
                {
                    usage = VertexElementUsage::Tangent;
                }
                else if (attribute.first == "WEIGHT")
                {
                    usage = VertexElementUsage::BlendWeight;
                }
                else
                {
                    std::cout << "unknown attribute [" << attribute.first << "]" << std::endl;
                }

                accessors.push_back(accessor);
                elements.push_back({ vertexStride, format, usage, ++usageIndex });

                vertexStride += accessor->byte_stride();
            }

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

            // Material
            // TODO: process material

            mesh->_mesh_parts.push_back(meshPart);
        }
    }
}
