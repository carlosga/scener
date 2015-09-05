// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TechniquesReader.hpp>

#include <iostream>

#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectPass.hpp>
#include <Graphics/EffectPassInstanceProgram.hpp>
#include <Graphics/EffectPassStates.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/RenderingStateType.hpp>
#include <Content/json11.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::Effect;
        using SceneR::Graphics::EffectParameter;
        using SceneR::Graphics::EffectParameterType;
        using SceneR::Graphics::EffectPass;
        using SceneR::Graphics::EffectPassInstanceProgram;
        using SceneR::Graphics::EffectPassStates;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::RenderingStateType;
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
            for (const auto& parameter : value.object_items())
            {
                auto tparameter = std::make_shared<EffectParameter>();

                tparameter->_count    = parameter.second["count"].int_value();
                tparameter->_type     = static_cast<EffectParameterType>(parameter.second["type"].int_value());
                tparameter->_semantic = parameter.second["semantic"].string_value();
                tparameter->_node     = parameter.second["node"].int_value();

                // TODO: Handle parameter value

                if (tparameter->_semantic.empty())
                {
                    // no semantic informed
                }
                else if (tparameter->_semantic == "MODELVIEW")
                {
                    technique->_model_view_matrix_param = tparameter;
                }
                else if (tparameter->_semantic == "PROJECTION")
                {
                    technique->_projection_matrix_param = tparameter;
                }
                else if (tparameter->_semantic == "MODELVIEWINVERSETRANSPOSE")
                {
                    technique->_normal_matrix_param = tparameter;
                }
                else if (tparameter->_semantic == "POSITION")
                {
                    technique->_position_param = tparameter;
                }
                else if (tparameter->_semantic == "NORMAL")
                {
                    technique->_normal_param = tparameter;
                }
                else if (tparameter->_semantic == "TEXCOORD_0")
                {
                    technique->_tex_coord_param = tparameter;
                }
                else if (tparameter->_semantic == "TEXBINORMAL")
                {
                    technique->_tex_binormal_param = tparameter;
                }
                else if (tparameter->_semantic == "TEXTANGENT")
                {
                    technique->_tex_tangent_param = tparameter;
                }
                else if (tparameter->_semantic == "JOINT")
                {
                    technique->_joint_param = tparameter;
                }
                else if (tparameter->_semantic == "JOINTMATRIX")
                {
                    technique->_joint_matrix_param = tparameter;
                }
                else if (tparameter->_semantic == "WEIGHT")
                {
                    technique->_weight_param = tparameter;
                }
                else
                {
                    std::cout << "unknown semantic [" << tparameter->_semantic << "]" << std::endl;
                }

                technique->_parameters[parameter.first] = tparameter;
            }
        }

        void TechniquesReader::read_technique_passes(const json11::Json& value, std::shared_ptr<Effect> technique)
        {
            for (const auto& pass : value.object_items())
            {
                auto       tpass    = std::make_shared<EffectPass>();
                const auto passName = pass.first;

                // Process only common profile details
                const auto& commonProfile = pass.second["details"]["commonProfile"];
                const auto& parameters    = commonProfile["parameters"];

                tpass->_lighting_model = commonProfile["lightingModel"].string_value();

                for (const auto& paramRef : parameters.array_items())
                {
                    tpass->_parameters.push_back(technique->_parameters[paramRef.string_value()]);
                }

                read_technique_pass_program(pass.second["instanceProgram"], technique, tpass);
                read_technique_pass_states(pass.second["states"], tpass);

                technique->_passes[pass.first] = tpass;
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
