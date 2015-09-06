// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TechniquesReader.hpp>

#include <iostream>

#include <Content/json11.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectPass.hpp>
#include <Graphics/EffectPassInstanceProgram.hpp>
#include <Graphics/EffectPassStates.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/RenderingStateType.hpp>

#include <System/Graphics/Platform.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::Effect;
        using SceneR::Graphics::EffectParameter;
        using SceneR::Graphics::EffectParameterClass;
        using SceneR::Graphics::EffectParameterType;
        using SceneR::Graphics::EffectPass;
        using SceneR::Graphics::EffectPassInstanceProgram;
        using SceneR::Graphics::EffectPassStates;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::RenderingStateType;
        using System::Text::Encoding;
        using json11::Json;

        TechniquesReader::TechniquesReader()
        {
        }

        TechniquesReader::~TechniquesReader()
        {
        }

        void TechniquesReader::read(const json11::Json&               value
                                  , SceneR::Graphics::GraphicsDevice& graphicsDevice
                                  , SceneR::Graphics::Model*          root)
        {
            for (const auto& item : value["techniques"].object_items())
            {
                auto technique = std::make_shared<Effect>(graphicsDevice);

                read_technique_parameters(item.second["parameters"], technique);
                read_technique_passes(item.second["passes"], technique);

                // Default pass
                technique->_pass = technique->_passes[item.second["pass"].string_value()];

                root->_techniques[item.first] = technique;
            }
        }

        void TechniquesReader::read_technique_parameters(const json11::Json& value, std::shared_ptr<Effect> technique)
        {
            for (const auto& source : value.object_items())
            {
                auto parameter = std::make_shared<EffectParameter>();
                auto type      = source.second["type"].int_value();

                parameter->_count    = source.second["count"].int_value();
                parameter->_semantic = Encoding::convert(source.second["semantic"].string_value());
                parameter->_node     = Encoding::convert(source.second["node"].string_value());

                describe_parameter(type, parameter);

                // TODO: Handle parameter value

                technique->_parameters[source.first] = parameter;
            }

            cache_parameters(technique);
        }

        void TechniquesReader::read_technique_passes(const json11::Json& value, std::shared_ptr<Effect> technique)
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

        void TechniquesReader::read_technique_pass_program(const json11::Json&         value
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

        void TechniquesReader::read_technique_pass_states(const json11::Json& value, std::shared_ptr<EffectPass> pass)
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

        void TechniquesReader::describe_parameter(const std::int32_t& type, std::shared_ptr<EffectParameter> parameter)
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

        // "pass":"defaultPass",
        // "passes":{
        //    "defaultPass":{
        //       "details":{
        //          "commonProfile":{
        //             "extras":{
        //                "doubleSided":false
        //             },
        //             "texcoordBindings":{
        //                "ambient":"TEXCOORD_0",
        //                "bump":"TEXCOORD_0",
        //                "diffuse":"TEXCOORD_0"
        //             }
        //          },
        //          "type":"COLLADA-1.4.1/commonProfile"
        //       },
        //       },
        //    }
    }
}
