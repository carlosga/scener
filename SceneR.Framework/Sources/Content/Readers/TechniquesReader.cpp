// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TechniquesReader.hpp>

#include <iostream>

#include <GLTF/Model.hpp>
#include <GLTF/TechniqueParameter.hpp>
#include <GLTF/TechniquePass.hpp>
#include <GLTF/TechniquePassInstanceProgram.hpp>
#include <GLTF/TechniquePassStates.hpp>
#include <Content/json11.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::GLTF::RenderingStateType;
        using SceneR::GLTF::Technique;
        using SceneR::GLTF::TechniqueParameter;
        using SceneR::GLTF::TechniqueParameterType;
        using SceneR::GLTF::TechniquePass;
        using SceneR::GLTF::TechniquePassInstanceProgram;
        using SceneR::GLTF::TechniquePassStates;
        using json11::Json;

        TechniquesReader::TechniquesReader()
        {
        }

        TechniquesReader::~TechniquesReader()
        {
        }

        void TechniquesReader::Read(const json11::Json& value, SceneR::GLTF::Model* root)
        {
            for (const auto& item : value["techniques"].object_items())
            {
                auto technique = std::make_shared<Technique>();

                this->ReadTechniqueParameters(item.second["parameters"], technique);
                this->ReadTechniquePasses(item.second["passes"], technique);

                // Default pass
                technique->pass = technique->passes[item.second["pass"].string_value()];

                root->techniques[item.first] = technique;
            }
        }

        void TechniquesReader::ReadTechniqueParameters(const json11::Json& value, std::shared_ptr<Technique> technique)
        {
            for (const auto& parameter : value.object_items())
            {
                auto tparameter = std::make_shared<TechniqueParameter>();

                tparameter->count    = parameter.second["count"].int_value();
                tparameter->type     = static_cast<TechniqueParameterType>(parameter.second["type"].int_value());
                tparameter->semantic = parameter.second["semantic"].string_value();
                tparameter->node     = parameter.second["node"].int_value();

                // TODO: Handle parameter value

                if (tparameter->semantic.empty())
                {
                    // no semantic informed
                }
                else if (tparameter->semantic == "MODELVIEW")
                {
                    technique->modelViewMatrix = tparameter;
                }
                else if (tparameter->semantic == "PROJECTION")
                {
                    technique->projectionMatrix = tparameter;
                }
                else if (tparameter->semantic == "MODELVIEWINVERSETRANSPOSE")
                {
                    technique->normalMatrix = tparameter;
                }
                else if (tparameter->semantic == "POSITION")
                {
                    technique->position = tparameter;
                }
                else if (tparameter->semantic == "NORMAL")
                {
                    technique->normal = tparameter;
                }
                else if (tparameter->semantic == "TEXCOORD_0")
                {
                    technique->texCoord = tparameter;
                }
                else if (tparameter->semantic == "TEXBINORMAL")
                {
                    technique->texBinormal = tparameter;
                }
                else if (tparameter->semantic == "TEXTANGENT")
                {
                    technique->texTangent = tparameter;
                }
                else if (tparameter->semantic == "JOINT")
                {
                    technique->joint = tparameter;
                }
                else if (tparameter->semantic == "JOINTMATRIX")
                {
                    technique->jointMatrix = tparameter;
                }
                else if (tparameter->semantic == "WEIGHT")
                {
                    technique->weight = tparameter;
                }
                else
                {
                    std::cout << "unknown semantic [" << tparameter->semantic << "]" << std::endl;
                }

                technique->parameters[parameter.first] = tparameter;
            }
        }

        void TechniquesReader::ReadTechniquePasses(const json11::Json& value, std::shared_ptr<Technique> technique)
        {
            for (const auto& pass : value.object_items())
            {
                auto       tpass    = std::make_shared<TechniquePass>();
                const auto passName = pass.first;

                // Process only common profile details
                const auto& commonProfile = pass.second["details"]["commonProfile"];
                const auto& parameters    = commonProfile["parameters"];

                tpass->lightingModel = commonProfile["lightingModel"].string_value();

                for (const auto& paramRef : parameters.array_items())
                {
                    tpass->parameters.push_back(technique->parameters[paramRef.string_value()]);
                }

                this->ReadTechniquePassProgram(pass.second["instanceProgram"], technique, tpass);
                this->ReadTechniquePassStates(pass.second["states"], tpass);

                technique->passes[pass.first] = tpass;
            }
        }

        void TechniquesReader::ReadTechniquePassProgram(const json11::Json&            value
                                                      , std::shared_ptr<Technique>     technique
                                                      , std::shared_ptr<TechniquePass> pass)
        {
            TechniquePassInstanceProgram program;

            program.name = value["program"].string_value();

            const auto& attributes = value["attributes"].object_items();
            const auto& uniforms   = value["uniforms"].object_items();

            for (const auto& attribute : attributes)
            {
                const std::string attName  = attribute.first;
                const std::string paramRef = attribute.second.string_value();

                program.attributes[attName] = technique->parameters[paramRef];
            }

            for (const auto& uniform : uniforms)
            {
                const std::string uniformName = uniform.first;
                const std::string paramRef    = uniform.second.string_value();

                program.uniforms[uniformName] = technique->parameters[paramRef];
            }

            pass->program = program;
        }

        void TechniquesReader::ReadTechniquePassStates(const json11::Json& value, std::shared_ptr<TechniquePass> pass)
        {
            TechniquePassStates passStates;

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
