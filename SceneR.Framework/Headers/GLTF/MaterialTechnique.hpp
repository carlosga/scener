// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATERIALTECHNIQUE_HPP
#define MATERIALTECHNIQUE_HPP

#include <memory>
// #include <GLTF/Technique.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class MaterialTechnique
        {
        public:
            MaterialTechnique() = default;
            ~MaterialTechnique() = default;

        public:
            // shd::shared_ptr<Technique> technique;

//            "properties": {
//                "technique" : {
//                    "extends" : { "$ref" : "glTFid.schema.json" },
//                    "description" : "The id (JSON property name) of the technique.",
//                            "required" : true
//                },
//                "values" : {
//                    "properties" : {
//                    },
//                    "additionalProperties" : {
//                        "$ref" : "materialInstanceTechniqueValues.schema.json"
//                    },
//                    "default" : {}
//                }
//            },
        };
    }
}

#endif // MATERIALTECHNIQUE_HPP
