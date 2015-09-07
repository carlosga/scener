// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TechniquesReader.hpp>

#include <iostream>

#include <Content/json11.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/Effect.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <Graphics/EffectPass.hpp>
#include <Graphics/EffectPassInstanceProgram.hpp>
#include <Graphics/EffectPassStates.hpp>
#include <Graphics/RenderingStateType.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Framework::Vector2;
        using SceneR::Framework::Vector3;
        using SceneR::Framework::Vector4;
        using SceneR::Graphics::Effect;
        using SceneR::Graphics::EffectParameter;
        using SceneR::Graphics::EffectParameterClass;
        using SceneR::Graphics::EffectParameterType;
        using SceneR::Graphics::EffectPass;
        using SceneR::Graphics::EffectPassInstanceProgram;
        using SceneR::Graphics::EffectPassStates;
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

                read_technique_parameters(item.second["parameters"], effect);
                read_technique_passes(item.second["passes"], effect);

                effect->name  = Encoding::convert(item.first);
                effect->_pass = effect->_passes[item.second["pass"].string_value()];

                context.effects.push_back(effect);
            }
        }

        void TechniquesReader::read_technique_parameters(const Json& value, std::shared_ptr<Effect> technique)
        {
            for (const auto& source : value.object_items())
            {
                auto parameter = std::make_shared<EffectParameter>();
                auto type      = source.second["type"].int_value();

                parameter->_count    = source.second["count"].int_value();
                parameter->_semantic = Encoding::convert(source.second["semantic"].string_value());
                parameter->_node     = Encoding::convert(source.second["node"].string_value());

                describe_parameter(parameter, type);

                auto node  = source.second["node"].string_value();

                set_parameter_value(parameter, source.second["value"]);

                // TODO : Node reference

                technique->_parameters[source.first] = parameter;
            }

            cache_parameters(technique);
        }

        void TechniquesReader::read_technique_passes(const Json& value, std::shared_ptr<Effect> technique)
        {
            for (const auto& source : value.object_items())
            {
                auto       pass     = std::make_shared<EffectPass>();
                const auto passName = source.first;

                // Process only common profile details
                const auto& commonProfile = source.second["details"]["commonProfile"];
                const auto& parameters    = commonProfile["parameters"];

                pass->_lighting_model = commonProfile["lightingModel"].string_value();

                for (const auto& paramRef : parameters.array_items())
                {
                    pass->_parameters.push_back(technique->_parameters[paramRef.string_value()]);
                }

                read_technique_pass_program(source.second["instanceProgram"], technique, pass);
                read_technique_pass_states(source.second["states"], pass);

                technique->_passes[source.first] = pass;
            }
        }

        void TechniquesReader::read_technique_pass_program(const Json&                 value
                                                         , std::shared_ptr<Effect>     technique
                                                         , std::shared_ptr<EffectPass> pass)
        {
            EffectPassInstanceProgram program;

            program._name = value["program"].string_value();

            const auto& attributes = value["attributes"].object_items();
            const auto& uniforms   = value["uniforms"].object_items();

            for (const auto& attribute : attributes)
            {
                const std::string attName  = attribute.first;
                const std::string paramRef = attribute.second.string_value();

                program._attributes[attName] = technique->_parameters[paramRef];
            }

            for (const auto& uniform : uniforms)
            {
                const std::string uniformName = uniform.first;
                const std::string paramRef    = uniform.second.string_value();

                program._uniforms[uniformName] = technique->_parameters[paramRef];
            }

            pass->_program = program;
        }

        void TechniquesReader::read_technique_pass_states(const Json& value, std::shared_ptr<EffectPass> pass)
        {
            EffectPassStates passStates;

            std::cout << value.dump() << std::endl;

            passStates.enabled = RenderingStateType::None;

            for (const auto& state : value["enable"].array_items())
            {
                passStates.enabled |= static_cast<RenderingStateType>(state.int_value());
            }
        }

        void TechniquesReader::cache_parameters(std::shared_ptr<Effect> technique)
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

        void TechniquesReader::describe_parameter(std::shared_ptr<EffectParameter> parameter, const std::int32_t& type)
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

        void TechniquesReader::set_parameter_value(std::shared_ptr<EffectParameter> parameter
                                                 , const Json&                      value)
        {
            if (value.is_null())
            {
            }
            else if (value.is_string())
            {
                //parameter->set_value(value.string_value());
            }
            else if (value.is_bool())
            {
                parameter->set_value(value.bool_value());
            }
            else if (value.is_number())
            {
                set_parameter_numeric_value(parameter, value);
            }
            else if (value.is_array())
            {
                std::vector<float> data;

                for (const auto& dataValue : value.array_items())
                {
                    data.push_back(dataValue.number_value());
                }

                if (parameter->parameter_class() == EffectParameterClass::Vector)
                {
                    set_parameter_vector_value(parameter, data);
                }
                else if (parameter->parameter_class() == EffectParameterClass::Matrix)
                {
                    // TODO: Handle matrix values
                }
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

        void TechniquesReader::set_parameter_vector_value(std::shared_ptr<EffectParameter> parameter
                                                        , std::vector<float>               data)
        {
            switch (parameter->column_count())
            {
            case 2:
                parameter->set_value(Vector2(data[0], data[1]));
                break;
            case 3:
                parameter->set_value(Vector3(data[0], data[1], data[2]));
                break;
            case 4:
                parameter->set_value(Vector4(data[0], data[1], data[2], data[3]));
                break;
            }
        }
    }
}
