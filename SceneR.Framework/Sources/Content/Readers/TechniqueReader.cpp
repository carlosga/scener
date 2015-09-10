// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TechniqueReader.hpp>

#include <iostream>

#include <Content/json11.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <Graphics/EffectPass.hpp>
#include <Graphics/EffectPassStates.hpp>
#include <Graphics/EffectTechnique.hpp>
#include <Graphics/Node.hpp>
#include <Graphics/Program.hpp>
#include <Graphics/RenderingStateType.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Vector2;
        using SceneR::Framework::Vector3;
        using SceneR::Framework::Vector4;
        using SceneR::Graphics::EffectTechnique;
        using SceneR::Graphics::EffectParameter;
        using SceneR::Graphics::EffectParameterClass;
        using SceneR::Graphics::EffectParameterType;
        using SceneR::Graphics::EffectPass;
        using SceneR::Graphics::EffectPassStates;
        using SceneR::Graphics::Node;
        using SceneR::Graphics::Program;
        using SceneR::Graphics::RenderingStateType;
        using System::Text::Encoding;

        ContentTypeReader<EffectTechnique>::ContentTypeReader()
        {
        }

        ContentTypeReader<EffectTechnique>::~ContentTypeReader()
        {
        }

        std::shared_ptr<EffectTechnique> ContentTypeReader<EffectTechnique>::read(const std::pair<std::string, Json>& source
                                                                                , ContentReaderContext&               context)
        {
            auto effect = std::make_shared<EffectTechnique>(context.graphics_device);

            read_technique_parameters(source.second["parameters"], context, effect);
            read_technique_passes(source.second["passes"], context, effect);
            cache_technique_parameters(effect);
            set_parameter_values(source.second["parameters"], context, effect);

            effect->name  = Encoding::convert(source.first);
            effect->_pass = effect->_passes[source.second["pass"].string_value()];

            return effect;
        }

        void ContentTypeReader<EffectTechnique>::read_technique_parameters(const Json&                      value
                                                                         , ContentReaderContext&            context
                                                                         , std::shared_ptr<EffectTechnique> effect)
        {
            for (const auto& source : value.object_items())
            {
                auto parameter = std::make_shared<EffectParameter>();
                auto type      = source.second["type"].int_value();

                parameter->_count    = source.second["count"].int_value();
                parameter->_semantic = Encoding::convert(source.second["semantic"].string_value());
                parameter->_node     = Encoding::convert(source.second["node"].string_value());

                describe_technique_parameter(parameter, type);

                effect->_parameters[source.first] = parameter;
            }
        }

        void ContentTypeReader<EffectTechnique>::set_parameter_values(const Json&                      value
                                                                    , ContentReaderContext&            context
                                                                    , std::shared_ptr<EffectTechnique> effect)
        {
            for (const auto& source : value.object_items())
            {
                auto        parameter  = effect->_parameters[source.first];
                auto        nodeId     = source.second["node"].string_value();
                const auto& paramValue = source.second["value"];

                if (!nodeId.empty())
                {
                    auto node = context.find_object<Node>(nodeId);

                    parameter->set_value<Matrix>(node->matrix);
                }
                else if (paramValue.is_null())
                {
                }
                else if (parameter->parameter_class() == EffectParameterClass::Scalar)
                {
                    switch (parameter->parameter_type())
                    {
                    case EffectParameterType::Bool:
                        parameter->set_value(paramValue.bool_value());
                        break;
                    case EffectParameterType::Byte:
                        parameter->set_value(static_cast<std::int8_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::UByte:
                        parameter->set_value(static_cast<std::uint8_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::Int16:
                        parameter->set_value(static_cast<std::int16_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::UInt16:
                        parameter->set_value(static_cast<std::uint16_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::Int32:
                        parameter->set_value(static_cast<std::int32_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::UInt32:
                        parameter->set_value(static_cast<std::uint32_t>(paramValue.int_value()));
                        break;
                    case EffectParameterType::Single:
                        parameter->set_value(static_cast<float>(paramValue.number_value()));
                        break;
                    case EffectParameterType::String:
                        parameter->set_value<std::u16string>(Encoding::convert(paramValue.string_value()));
                        break;
                    }
                }
                else  if (parameter->parameter_class() == EffectParameterClass::Vector)
                {
                    switch (parameter->column_count())
                    {
                    case 2:
                        parameter->set_value<Vector2>(context.convert<Vector2>(paramValue.array_items()));
                        break;
                    case 3:
                        parameter->set_value<Vector3>(context.convert<Vector3>(paramValue.array_items()));
                        break;
                    case 4:
                        parameter->set_value<Vector4>(context.convert<Vector4>(paramValue.array_items()));
                        break;
                    }
                }
                else if (parameter->parameter_class() == EffectParameterClass::Matrix)
                {
                    parameter->set_value<Matrix>(context.convert<Matrix>(paramValue.array_items()));
                }
            }
        }

        void ContentTypeReader<EffectTechnique>::read_technique_passes(const Json&                      value
                                                                     , ContentReaderContext&            context
                                                                     , std::shared_ptr<EffectTechnique> effect)
        {
            for (const auto& source : value.object_items())
            {
                auto       pass     = std::make_shared<EffectPass>();
                const auto passName = source.first;

                // Process only common profile details
                const auto& commonProfile = source.second["details"]["commonProfile"];
                const auto& parameters    = commonProfile["parameters"];

                pass->_name           = Encoding::convert(source.first);
                pass->_lighting_model = Encoding::convert(commonProfile["lightingModel"].string_value());

                for (const auto& paramRef : parameters.array_items())
                {
                    pass->_parameters.push_back(effect->_parameters[paramRef.string_value()]);
                }

                read_technique_pass_program(source.second["instanceProgram"], context, effect, pass);
                read_technique_pass_states(source.second["states"], pass);

                effect->_passes[source.first] = pass;
            }
        }

        void ContentTypeReader<EffectTechnique>::read_technique_pass_program(const Json&                      value
                                                                           , ContentReaderContext&            context
                                                                           , std::shared_ptr<EffectTechnique> effect
                                                                           , std::shared_ptr<EffectPass>      effectPass)
        {
            // Pass program
            effectPass->_program = context.find_object<Program>(value["program"].string_value());

            // Attributes
            // ignored, they should be passed in the vertex buffer

            // Uniforms
            const auto& uniforms = value["uniforms"].object_items();
            auto        offsets  = effectPass->_program->get_uniform_offsets();

            for (const auto& uniform : uniforms)
            {
                auto uniformName = uniform.first;
                auto parameter   = effect->_parameters[uniform.second.string_value()];

                parameter->_offset         = offsets[uniformName];
                parameter->_uniform_buffer = effectPass->_program->uniform_buffer();
            }
        }

        void ContentTypeReader<EffectTechnique>::read_technique_pass_states(const Json&                 value
                                                                          , std::shared_ptr<EffectPass> effectPass)
        {
            EffectPassStates passStates;

            std::cout << value.dump() << std::endl;

            passStates.enabled = RenderingStateType::None;

            for (const auto& state : value["enable"].array_items())
            {
                passStates.enabled |= static_cast<RenderingStateType>(state.int_value());
            }
        }

        void ContentTypeReader<EffectTechnique>::cache_technique_parameters(std::shared_ptr<EffectTechnique> technique)
        {
            for (auto parameter : technique->_parameters)
            {
                if (parameter.second->_semantic.empty())
                {
                    // no semantic informed
                }
                else if (parameter.second->_semantic == u"MODELVIEW")
                {
                    technique->_model_view_matrix_param = parameter.second;
                }
                else if (parameter.second->_semantic == u"PROJECTION")
                {
                    technique->_projection_matrix_param = parameter.second;
                }
                else if (parameter.second->_semantic == u"MODELVIEWINVERSETRANSPOSE")
                {
                    technique->_normal_matrix_param = parameter.second;
                }
                else if (parameter.second->_semantic == u"POSITION")
                {
                    technique->_position_param = parameter.second;
                }
                else if (parameter.second->_semantic == u"NORMAL")
                {
                    technique->_normal_param = parameter.second;
                }
                else if (parameter.second->_semantic == u"TEXCOORD_0")
                {
                    technique->_tex_coord_param = parameter.second;
                }
                else if (parameter.second->_semantic == u"TEXBINORMAL")
                {
                    technique->_tex_binormal_param = parameter.second;
                }
                else if (parameter.second->_semantic == u"TEXTANGENT")
                {
                    technique->_tex_tangent_param = parameter.second;
                }
                else if (parameter.second->_semantic == u"JOINT")
                {
                    technique->_joint_param = parameter.second;
                }
                else if (parameter.second->_semantic == u"JOINTMATRIX")
                {
                    technique->_joint_matrix_param = parameter.second;
                }
                else if (parameter.second->_semantic == u"WEIGHT")
                {
                    technique->_weight_param = parameter.second;
                }
                else
                {
                    std::cout << "unknown semantic [" << Encoding::convert(parameter.second->_semantic) << "]" << std::endl;
                }
            }
        }

        void ContentTypeReader<EffectTechnique>::describe_technique_parameter(std::shared_ptr<EffectParameter> parameter
                                                                            , const std::int32_t&              type)
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
