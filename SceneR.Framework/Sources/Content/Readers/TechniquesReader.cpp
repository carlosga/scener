// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/TechniquesReader.hpp>

#include <iostream>

#include <GLTF/Model.hpp>
#include <GLTF/TechniqueParameterType.hpp>
#include <Content/json11.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::GLTF::Technique;
        using SceneR::GLTF::TechniqueParameter;
        using SceneR::GLTF::TechniqueParameterType;
        using SceneR::GLTF::TechniquePass;
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

                this->ReadTechniqueParameters(item.second, root, technique);
                this->ReadTechniquePasses(item.second, root, technique);

                root->techniques[item.first] = technique;
            }
        }

        void TechniquesReader::ReadTechniqueParameters(const json11::Json&        value
                                                     , SceneR::GLTF::Model*       root
                                                     , std::shared_ptr<Technique> technique)
        {
            const auto& parameters = value["parameters"].object_items();

            for (const auto& parameter : parameters)
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

                technique->parameters.push_back(tparameter);
            }
        }

        void TechniquesReader::ReadTechniquePasses(const json11::Json&                      value
                                                 , SceneR::GLTF::Model*                     root
                                                 , std::shared_ptr<SceneR::GLTF::Technique> technique)
        {
            const auto  defaultPass = value["pass"].string_value();
            const auto& passes      = value["passes"].object_items();

            for (const auto& pass : passes)
            {
                auto       tpass    = std::make_shared<TechniquePass>();
                const auto passName = pass.first;

                if (passName == defaultPass)
                {
                    technique->pass = tpass;
                }

                technique->passes.push_back(tpass);
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
        //             "lightingModel":"Blinn",
        //             "parameters":[
        //                "ambient",
        //                "bump",
        //                "diffuse",
        //                "emission",
        //                "jointMat",
        //                "light0Color",
        //                "light1Color",
        //                "light1ConstantAttenuation",
        //                "light1LinearAttenuation",
        //                "light1QuadraticAttenuation",
        //                "light1Transform",
        //                "modelViewMatrix",
        //                "normalMatrix",
        //                "projectionMatrix",
        //                "shininess",
        //                "specular"
        //             ],
        //             "texcoordBindings":{
        //                "ambient":"TEXCOORD_0",
        //                "bump":"TEXCOORD_0",
        //                "diffuse":"TEXCOORD_0"
        //             }
        //          },
        //          "type":"COLLADA-1.4.1/commonProfile"
        //       },
        //       "instanceProgram":{
        //          "attributes":{
        //             "a_joint":"joint",
        //             "a_normal":"normal",
        //             "a_position":"position",
        //             "a_texbinormal":"texbinormal",
        //             "a_texcoord0":"texcoord0",
        //             "a_textangent":"textangent",
        //             "a_weight":"weight"
        //          },
        //          "program":"program_0",
        //          "uniforms":{
        //             "u_ambient":"ambient",
        //             "u_bump":"bump",
        //             "u_diffuse":"diffuse",
        //             "u_emission":"emission",
        //             "u_jointMat":"jointMat",
        //             "u_light0Color":"light0Color",
        //             "u_light1Color":"light1Color",
        //             "u_light1ConstantAttenuation":"light1ConstantAttenuation",
        //             "u_light1LinearAttenuation":"light1LinearAttenuation",
        //             "u_light1QuadraticAttenuation":"light1QuadraticAttenuation",
        //             "u_light1Transform":"light1Transform",
        //             "u_modelViewMatrix":"modelViewMatrix",
        //             "u_normalMatrix":"normalMatrix",
        //             "u_projectionMatrix":"projectionMatrix",
        //             "u_shininess":"shininess",
        //             "u_specular":"specular"
        //          }
        //       },
        //       "states":{
        //          "enable":[
        //             2884,
        //             2929
        //          ]
        //       }
        //    }
    }
}
