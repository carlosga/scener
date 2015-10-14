// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ModelMeshReader.hpp>

#include <iostream>

#include <json11.hpp>
#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/BufferObject.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <Graphics/EffectTechnique.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/Texture2D.hpp>
#include <Graphics/VertexArrayObject.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexDeclaration.hpp>

using json11::Json;
using SceneR::Content::ContentTypeReader;
using SceneR::Framework::Matrix;
using SceneR::Framework::Vector2;
using SceneR::Framework::Vector3;
using SceneR::Framework::Vector4;
using SceneR::Graphics::Accessor;
using SceneR::Graphics::AttributeType;
using SceneR::Graphics::ComponentType;
using SceneR::Graphics::EffectParameter;
using SceneR::Graphics::EffectParameterClass;
using SceneR::Graphics::EffectParameterType;
using SceneR::Graphics::EffectTechnique;
using SceneR::Graphics::IGraphicsDeviceService;
using SceneR::Graphics::IndexBuffer;
using SceneR::Graphics::Model;
using SceneR::Graphics::ModelMesh;
using SceneR::Graphics::ModelMeshPart;
using SceneR::Graphics::PrimitiveType;
using SceneR::Graphics::Texture2D;
using SceneR::Graphics::VertexBuffer;
using SceneR::Graphics::VertexDeclaration;
using SceneR::Graphics::VertexElement;
using SceneR::Graphics::VertexElementFormat;
using SceneR::Graphics::VertexElementUsage;

namespace SceneR
{
    namespace Content
    {
        std::shared_ptr<ModelMesh> ContentTypeReader<ModelMesh>::read(gsl::not_null<ContentReader*>       input
                                                                    , const std::pair<std::string, Json>& source) const
        {
            auto mesh = std::make_shared<ModelMesh>();

            mesh->_name = source.first;

            for (const auto& primitive : source.second["primitives"].array_items())
            {
                read_mesh_part(input, primitive, mesh.get());
            }

            return mesh;
        }

        void ContentTypeReader<ModelMesh>::read_mesh_part(gsl::not_null<ContentReader*> input
                                                        , const json11::Json&           source
                                                        , ModelMesh*                    mesh) const
        {
            auto gdService     = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
            auto device        = gdService->graphics_device();
            auto meshPart      = std::make_shared<ModelMeshPart>();
            auto accessors     = std::vector<std::shared_ptr<Accessor>>();
            auto elements      = std::vector<VertexElement>();
            auto vertexStride  = std::size_t(0);
            auto vertexCount   = std::size_t(0);
            auto indices       = input->read_object<Accessor>(source["indices"].string_value());
            auto componentType = indices->component_type();
            auto indexCount    = indices->attribute_count();
            auto indexData     = indices->get_data();

            // Index buffer
            meshPart->_index_buffer = std::make_unique<IndexBuffer>(device, componentType, indexCount);
            meshPart->_index_buffer->initialize();
            meshPart->_index_buffer->set_data(indexData);

            // Vertex buffer
            for (const auto& attribute : source["attributes"].object_items())
            {
                const auto accessor   = input->read_object<Accessor>(attribute.second.string_value());
                const auto format     = get_vertex_element_format(accessor->attribute_type());
                const auto usage      = get_vertex_element_usage(attribute.first);
                const auto usageIndex = static_cast<std::uint32_t>(usage);

                if (usage == VertexElementUsage::Position)
                {
                    vertexCount = accessor->attribute_count();
                }

                accessors.push_back(accessor);
                elements.push_back({ vertexStride, format, usage, usageIndex });

                vertexStride += accessor->byte_stride();
            }

            auto declaration = std::make_unique<VertexDeclaration>(vertexStride, elements);

            meshPart->_primitive_type  = static_cast<PrimitiveType>(source["mode"].int_value());
            meshPart->_vertex_count    = vertexCount;
            meshPart->_start_index     = 0;
            meshPart->_vertex_offset   = 0;
            meshPart->_primitive_count = 0;
            meshPart->_vertex_buffer   = std::make_unique<VertexBuffer>(device, vertexCount, std::move(declaration));

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
                for (const auto accessor : accessors)
                {
                    const auto view = accessor->get_data(i, 1);

                    std::copy_n(view.begin(), accessor->byte_stride(), position);

                    position += accessor->byte_stride();
                }
            }

            // Initialize vertex buffer
            meshPart->_vertex_buffer->initialize();
            meshPart->_vertex_buffer->set_data(vertexData);

            // Effect Material
            auto materialRef = source["material"].string_value();
            if (!materialRef.empty())
            {
                meshPart->effect = read_material(input, materialRef);
            }

            mesh->_mesh_parts.push_back(meshPart);
        }

        std::shared_ptr<EffectTechnique> ContentTypeReader<ModelMesh>::read_material(gsl::not_null<ContentReader*> input
                                                                                   , const std::string&            name) const
        {
            const auto& material     = input->_root["materials"][name];
            const auto& itechnique   = material["instanceTechnique"];
            const auto& values       = itechnique["values"].object_items();
            const auto  techniqueRef = itechnique["technique"].string_value();
            auto        technique    = input->read_object_instance<EffectTechnique>(techniqueRef);

            for (const auto& value : values)
            {
                auto        parameter  = technique->_parameters[value.first];
                const auto& paramValue = value.second;

                if (paramValue.is_null())
                {
                }
                else if (parameter->parameter_class() == EffectParameterClass::Scalar)
                {
                    switch (parameter->parameter_type())
                    {
                    case EffectParameterType::Bool:
                        parameter->set_value<bool>(paramValue.bool_value());
                        break;
                    case EffectParameterType::Byte:
                        parameter->set_value<std::int8_t>(static_cast<std::int8_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::UByte:
                        parameter->set_value<std::uint8_t>(static_cast<std::uint8_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::Int16:
                        parameter->set_value<std::int16_t>(static_cast<std::int16_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::UInt16:
                        parameter->set_value<std::uint16_t>(static_cast<std::uint16_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::Int32:
                        parameter->set_value<std::int32_t>(static_cast<std::int32_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::UInt32:
                        parameter->set_value<std::uint32_t>(static_cast<std::uint32_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::Single:
                        parameter->set_value<float>(static_cast<float>(paramValue.number_value()));
                        break;
                    case EffectParameterType::String:
                        parameter->set_value<std::string>(paramValue.string_value());
                        break;
                    default:
                        std::cout << "unknown parameter type" << std::endl;
                        break;
                    }
                }
                else  if (parameter->parameter_class() == EffectParameterClass::Vector)
                {
                    switch (parameter->column_count())
                    {
                    case 2:
                        parameter->set_value<Vector2>(input->convert<Vector2>(paramValue.array_items()));
                        break;
                    case 3:
                        parameter->set_value<Vector3>(input->convert<Vector3>(paramValue.array_items()));
                        break;
                    case 4:
                        parameter->set_value<Vector4>(input->convert<Vector4>(paramValue.array_items()));
                        break;
                    }
                }
                else if (parameter->parameter_class() == EffectParameterClass::Matrix)
                {
                    parameter->set_value<Matrix>(input->convert<Matrix>(paramValue.array_items()));
                }
                else if (parameter->parameter_class() == EffectParameterClass::Object)
                {
                    technique->textures().push_back(input->read_object<Texture2D>(paramValue.string_value()));
                }
            }

            return technique;
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

            throw std::runtime_error("unsupported attribute type");
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
