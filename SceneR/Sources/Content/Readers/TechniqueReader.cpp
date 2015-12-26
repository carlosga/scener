// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TechniqueReader.hpp>

#include <json11.hpp>
#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Content/Readers/Node.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <Graphics/EffectPass.hpp>
#include <Graphics/EffectTechnique.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/Program.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Vector2;
        using SceneR::Framework::Vector3;
        using SceneR::Framework::Vector4;
        using SceneR::Content::Node;
        using SceneR::Graphics::EffectTechnique;
        using SceneR::Graphics::EffectParameter;
        using SceneR::Graphics::EffectParameterClass;
        using SceneR::Graphics::EffectParameterType;
        using SceneR::Graphics::EffectPass;
        using SceneR::Graphics::IGraphicsDeviceService;
        using SceneR::Graphics::Program;

        std::shared_ptr<EffectTechnique> ContentTypeReader<EffectTechnique>::read(gsl::not_null<ContentReader*> input
                                                                                , const std::pair<std::string, Json>& source) const
        {
            auto gdService = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
            auto effect    = std::make_shared<EffectTechnique>(gdService->graphics_device());

            read_parameters(input, source.second, effect.get());
            add_default_pass(input, source.second, effect.get());
            cache_parameters(effect.get());
            set_parameter_values(input, source.second["parameters"], effect.get());

            effect->name = source.first;

            return effect;
        }

        void ContentTypeReader<EffectTechnique>::read_parameters(ContentReader*   input
                                                               , const Json&      source
                                                               , EffectTechnique* effect) const
        {
            for (const auto& uniform : source["uniforms"].object_items())
            {
                auto parameter = std::make_shared<EffectParameter>();
                auto paramRef  = source["parameters"][uniform.second.string_value()];

                parameter->_name         = uniform.second.string_value();
                parameter->_uniform_name = uniform.first;
                parameter->_count        = paramRef["count"].int_value();

                if (paramRef["node"].is_null() && !paramRef["semantic"].is_null())
                {
                    parameter->_semantic = paramRef["semantic"].string_value();
                }

                describe_parameter(parameter.get(), paramRef["type"].int_value());

                effect->_parameters[parameter->_name] = parameter;
            }
        }

        void ContentTypeReader<EffectTechnique>::set_parameter_values(ContentReader*   input
                                                                    , const Json&      value
                                                                    , EffectTechnique* effect) const
        {
            for (const auto& source : value.object_items())
            {
                auto        nodeId     = source.second["node"].string_value();
                const auto& paramValue = source.second["value"];
                auto        parameter  = effect->_parameters[source.first];

                if (parameter == nullptr || paramValue.is_null())
                {
                    continue;
                }

                if (!nodeId.empty())
                {
                    // TODO: Read node reference
                    // auto node = context.find_object<Node>(nodeId);
                    // parameter->set_value<Matrix>(node->matrix);
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
                        throw std::runtime_error("unknown parameter type");
                        break;
                    }
                }
                else if (parameter->parameter_class() == EffectParameterClass::Vector)
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
            }
        }

        void ContentTypeReader<EffectTechnique>::add_default_pass(ContentReader*                     input
                                                                , const json11::Json&                source
                                                                , SceneR::Graphics::EffectTechnique* effect) const
        {
            auto gdService = input->content_manager()->service_provider()->get_service<IGraphicsDeviceService>();
            auto pass      = std::make_shared<EffectPass>(gdService->graphics_device());

            pass->_name = "default_pass";

            for (const auto& param : effect->_parameters)
            {
                pass->_parameters.push_back(param.second);
            }

            read_pass_program(input, source["program"].string_value(), pass.get());

            effect->_passes.push_back(pass);
            effect->_pass = pass;
        }

        void ContentTypeReader<EffectTechnique>::read_pass_program(ContentReader*     input
                                                                 , const std::string& programName
                                                                 , EffectPass*        effectPass) const
        {
            // Pass program
            effectPass->_program = input->read_object_instance<Program>(programName);

            // Attributes
            // ignored, they should be passed in the vertex buffer

            // Uniforms
            auto offsets = effectPass->_program->get_uniform_offsets();

            for (auto parameter : effectPass->_parameters)
            {
                if (offsets.find(parameter->_uniform_name) != offsets.end())
                {
                    parameter->_offset         = offsets[parameter->_uniform_name];
                    parameter->_uniform_buffer = effectPass->_program->uniform_buffer();
                }
            }
        }

        void ContentTypeReader<EffectTechnique>::cache_parameters(EffectTechnique* technique) const
        {
            for (auto parameter : technique->_parameters)
            {
                if (parameter.second->_semantic.empty())
                {
                    continue;
                }

                if (parameter.second->_semantic == "MODEL")
                {
                    technique->_world_param = parameter.second;
                }
                else if (parameter.second->_semantic == "VIEW")
                {
                    technique->_view_param = parameter.second;
                }
                else if (parameter.second->_semantic == "PROJECTION")
                {
                    technique->_projection_param = parameter.second;
                }
                else if (parameter.second->_semantic == "MODELVIEW")
                {
                    technique->_world_view_param = parameter.second;
                }
                else if (parameter.second->_semantic == "MODELVIEWPROJECTION")
                {
                    technique->_world_view_projection_param = parameter.second;
                }
                else if (parameter.second->_semantic == "MODELINVERSE")
                {
                    technique->_world_inverse_param = parameter.second;
                }
                else if (parameter.second->_semantic == "VIEWINVERSE")
                {
                    technique->_view_inverse_param = parameter.second;
                }
                else if (parameter.second->_semantic == "PROJECTIONINVERSE")
                {
                    technique->_projection_inverse_param = parameter.second;
                }
                else if (parameter.second->_semantic == "MODELVIEWINVERSE")
                {
                    technique->_world_view_inverse_param = parameter.second;
                }
                else if (parameter.second->_semantic == "MODELVIEWPROJECTIONINVERSE")
                {
                    technique->_world_view_projection_inverse_param = parameter.second;
                }
                else if (parameter.second->_semantic == "MODELINVERSETRANSPOSE")
                {
                    technique->_world_inverse_transpose_param = parameter.second;
                }
                else if (parameter.second->_semantic == "MODELVIEWINVERSETRANSPOSE")
                {
                    technique->_world_view_inverse_transpose_param = parameter.second;
                }
                else if (parameter.second->_semantic == "JOINTMATRIX")
                {
                    technique->_bones_param = parameter.second;
                }
            }
        }

        void ContentTypeReader<EffectTechnique>::describe_parameter(EffectParameter*    parameter
                                                                  , const std::int32_t& type) const
        {
            switch (type)
            {
            case GL_BYTE:
                parameter->_parameter_class = EffectParameterClass::Scalar;
                parameter->_parameter_type  = EffectParameterType::Byte;
                break;

            case GL_UNSIGNED_BYTE:
                parameter->_parameter_class = EffectParameterClass::Scalar;
                parameter->_parameter_type  = EffectParameterType::Byte;
                break;

            case GL_SHORT:
                parameter->_parameter_class = EffectParameterClass::Scalar;
                parameter->_parameter_type  = EffectParameterType::Int16;
                break;

            case GL_UNSIGNED_SHORT:
                parameter->_parameter_class = EffectParameterClass::Scalar;
                parameter->_parameter_type  = EffectParameterType::UInt16;
                break;

            case GL_INT:
                parameter->_parameter_class = EffectParameterClass::Scalar;
                parameter->_parameter_type  = EffectParameterType::Int32;
                break;

            case GL_UNSIGNED_INT:
                parameter->_parameter_class = EffectParameterClass::Scalar;
                parameter->_parameter_type  = EffectParameterType::UInt32;
                break;

            case GL_FLOAT:
                parameter->_parameter_class = EffectParameterClass::Scalar;
                parameter->_parameter_type  = EffectParameterType::Single;
                break;

            case GL_FLOAT_VEC2:
                parameter->_parameter_class = EffectParameterClass::Vector;
                parameter->_parameter_type  = EffectParameterType::Single;
                parameter->_row_count       = 1;
                parameter->_column_count    = 2;
                break;

            case GL_FLOAT_VEC3:
                parameter->_parameter_class = EffectParameterClass::Vector;
                parameter->_parameter_type  = EffectParameterType::Single;
                parameter->_row_count       = 1;
                parameter->_column_count    = 3;
                break;

            case GL_FLOAT_VEC4:
                parameter->_parameter_class = EffectParameterClass::Vector;
                parameter->_parameter_type  = EffectParameterType::Single;
                parameter->_row_count       = 1;
                parameter->_column_count    = 4;
                break;

            case GL_INT_VEC2:
                parameter->_parameter_class = EffectParameterClass::Vector;
                parameter->_parameter_type  = EffectParameterType::Int32;
                parameter->_row_count       = 1;
                parameter->_column_count    = 2;
                break;

            case GL_INT_VEC3:
                parameter->_parameter_class = EffectParameterClass::Vector;
                parameter->_parameter_type  = EffectParameterType::Int32;
                parameter->_row_count       = 1;
                parameter->_column_count    = 3;
                break;

            case GL_INT_VEC4:
                parameter->_parameter_class = EffectParameterClass::Vector;
                parameter->_parameter_type  = EffectParameterType::Int32;
                parameter->_row_count       = 1;
                parameter->_column_count    = 4;
                break;

            case GL_BOOL:
                parameter->_parameter_class = EffectParameterClass::Scalar;
                parameter->_parameter_type  = EffectParameterType::Bool;
                break;

            case GL_BOOL_VEC2:
                parameter->_parameter_class = EffectParameterClass::Vector;
                parameter->_parameter_type  = EffectParameterType::Bool;
                parameter->_row_count       = 1;
                parameter->_column_count    = 2;
                break;

            case GL_BOOL_VEC3:
                parameter->_parameter_class = EffectParameterClass::Vector;
                parameter->_parameter_type  = EffectParameterType::Bool;
                parameter->_row_count       = 1;
                parameter->_column_count    = 3;
                break;

            case GL_BOOL_VEC4:
                parameter->_parameter_class = EffectParameterClass::Vector;
                parameter->_parameter_type  = EffectParameterType::Bool;
                parameter->_row_count       = 1;
                parameter->_column_count    = 4;
                break;

            case GL_FLOAT_MAT2	: // mat2
                parameter->_parameter_class = EffectParameterClass::Matrix;
                parameter->_parameter_type  = EffectParameterType::Single;
                parameter->_row_count       = 2;
                parameter->_column_count    = 2;
                break;

            case GL_FLOAT_MAT3	: // mat3
                parameter->_parameter_class = EffectParameterClass::Matrix;
                parameter->_parameter_type  = EffectParameterType::Single;
                parameter->_row_count       = 3;
                parameter->_column_count    = 3;
                break;

            case GL_FLOAT_MAT4	: // mat4
                parameter->_parameter_class = EffectParameterClass::Matrix;
                parameter->_parameter_type  = EffectParameterType::Single;
                parameter->_row_count       = 4;
                parameter->_column_count    = 4;
                break;

            case GL_SAMPLER_2D:
                parameter->_parameter_class = EffectParameterClass::Object;
                parameter->_parameter_type  = EffectParameterType::Texture2D;
                break;
            }
        }
    }
}
