// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TechniquesReader.hpp>

#include <iostream>

#include <Content/json11.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/Effect.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <Graphics/EffectPass.hpp>
#include <Graphics/EffectPassStates.hpp>
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
        using SceneR::Graphics::Effect;
        using SceneR::Graphics::EffectParameter;
        using SceneR::Graphics::EffectParameterClass;
        using SceneR::Graphics::EffectParameterType;
        using SceneR::Graphics::EffectPass;
        using SceneR::Graphics::EffectPassStates;
        using SceneR::Graphics::Node;
        using SceneR::Graphics::Program;
        using SceneR::Graphics::RenderingStateType;
        using System::Text::Encoding;

        TechniquesReader::TechniquesReader()
        {
        }

        TechniquesReader::~TechniquesReader()
        {
        }

        void TechniquesReader::read(const json11::Json& value, ContentReaderContext& context)
        {
            for (const auto& item : value["techniques"].object_items())
            {
                auto effect = std::make_shared<Effect>(context.graphics_device);

                read_technique_parameters(item.second["parameters"], context, effect);
                read_technique_passes(item.second["passes"], context, effect);
                cache_technique_parameters(effect);
                set_parameter_values(item.second["parameters"], context, effect);

                effect->name  = Encoding::convert(item.first);
                effect->_pass = effect->_passes[item.second["pass"].string_value()];

                context.effects.push_back(effect);
            }
        }

        void TechniquesReader::read_technique_parameters(const Json&             value
                                                       , ContentReaderContext&   context
                                                       , std::shared_ptr<Effect> effect)
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

        void TechniquesReader::set_parameter_values(const Json&             value
                                                  , ContentReaderContext&   context
                                                  , std::shared_ptr<Effect> effect)
        {
            for (const auto& source : value.object_items())
            {
                auto parameter = effect->_parameters[source.first];
                auto nodeId    = source.second["node"].string_value();

                if (!nodeId.empty())
                {
                    auto node = context.find_object<Node>(nodeId);

                    parameter->set_value<Matrix>(node->matrix);
                }
                else
                {
                    const auto& paramValue = source.second["value"];

                    if (paramValue.is_null())
                    {

                    }
                    else if (paramValue.is_string())
                    {
                        parameter->set_value<std::u16string>(Encoding::convert(paramValue.string_value()));
                    }
                    else if (paramValue.is_bool())
                    {
                        parameter->set_value<bool>(paramValue.bool_value());
                    }
                    else if (paramValue.is_number())
                    {
                        set_parameter_numeric_value(parameter, paramValue);
                    }
                    else if (paramValue.is_array())
                    {
                        if (parameter->parameter_class() == EffectParameterClass::Vector)
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
            }
        }

        void TechniquesReader::read_technique_passes(const Json&             value
                                                   , ContentReaderContext&   context
                                                   , std::shared_ptr<Effect> effect)
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

        void TechniquesReader::read_technique_pass_program(const Json&                 value
                                                         , ContentReaderContext&       context
                                                         , std::shared_ptr<Effect>     effect
                                                         , std::shared_ptr<EffectPass> effectPass)
        {
            // Pass program
            effectPass->_program = context.find_object<Program>(value["program"].string_value());

            // Attributes
            // const auto& attributes = value["attributes"].object_items();

            // for (const auto& attribute : attributes)
            // {
            //     const auto attName  = attribute.first;
            //     const auto paramRef = attribute.second.string_value();

            //     effectPass->_program->_attributes[attName] = effect->_parameters[paramRef];
            // }

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

        void TechniquesReader::read_technique_pass_states(const Json& value, std::shared_ptr<EffectPass> effectPass)
        {
            EffectPassStates passStates;

            std::cout << value.dump() << std::endl;

            passStates.enabled = RenderingStateType::None;

            for (const auto& state : value["enable"].array_items())
            {
                passStates.enabled |= static_cast<RenderingStateType>(state.int_value());
            }
        }

        void TechniquesReader::cache_technique_parameters(std::shared_ptr<Effect> technique)
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

        void TechniquesReader::describe_technique_parameter(std::shared_ptr<EffectParameter> parameter
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

        void TechniquesReader::set_parameter_numeric_value(std::shared_ptr<EffectParameter> parameter
                                                         , const json11::Json&              value)
        {
            switch (parameter->parameter_type())
            {
            case EffectParameterType::Byte:
                parameter->set_value(static_cast<std::int8_t>(value.is_number()));
                break;
            case EffectParameterType::UByte:
                parameter->set_value(static_cast<std::uint8_t>(value.is_number()));
                break;
            case EffectParameterType::Int16:
                parameter->set_value(static_cast<std::int16_t>(value.is_number()));
                break;
            case EffectParameterType::UInt16:
                parameter->set_value(static_cast<std::uint16_t>(value.is_number()));
                break;
            case EffectParameterType::Int32:
                parameter->set_value(static_cast<std::int32_t>(value.is_number()));
                break;
            case EffectParameterType::UInt32:
                parameter->set_value(static_cast<std::uint32_t>(value.is_number()));
                break;
            case EffectParameterType::Single:
                parameter->set_value(static_cast<float>(value.is_number()));
                break;
            }
        }
    }
}
