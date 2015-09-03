// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHNIQUE_HPP
#define TECHNIQUE_HPP

#include <memory>
#include <string>
#include <vector>

#include <GLTF/TechiqueParameter.hpp>
#include <GLTF/TechiquePass.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class Technique
        {
        public:
            Technique() = default;
            ~Technique() = default;

        public:
            std::vector<TechniqueParameter>             parameters;
            std::shared_ptr<TechniquePass>              pass;
            std::vector<std::shared_ptr<TechniquePass>> passes;

//            "parameters" : {
//                "properties" : {
//                },
//                "additionalProperties" : {
//                    "$ref" : "techniqueParameters.schema.json"
//                },
//                "default" : {}
//            },
//            "pass" : {
//                "extends" : { "$ref" : "glTFid.schema.json" },
//                "description" : "The id (JSON property name) of the default pass to use.",
//                    "required" : true
//            },
//            "passes" : {
//                "properties" : {
//                },
//                "additionalProperties" : {
//                    "$ref" : "techniquePass.schema.json"
//                },
//                "required" : true
//            }

        };
    }
}

#endif // TECHNIQUE_HPP
