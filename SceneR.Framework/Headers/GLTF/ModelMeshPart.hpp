// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MODELMESHPART_HPP
#define MODELMESHPART_HPP

#include <map>
#include <memory>
#include <GLTF/Accessor.hpp>
#include <GLTF/Material.hpp>
#include <Graphics/PrimitiveType.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class ModelMeshPart
        {
        public:
            ModelMeshPart() = default;
            ~ModelMeshPart() = default;

        public:
//            "properties" : {
//                "attributes" : {
//                    "properties" : {
//                    },
//                    "additionalProperties" : {
//                        "$ref" : "meshPrimitiveAttribute.schema.json"
//                    },
//                    "default" : {}
//                },
//                "indices" : {
//                    "extends" : { "$ref" : "glTFid.schema.json" },
//                    "description" : "The id (JSON property name) of the accessor that contains the indices.",
//                            "required" : true
//                },
//                "material" : {
//                    "extends" : { "$ref" : "glTFid.schema.json" },
//                    "description" : "The id (JSON property name) of the material to apply to this primitive when rendering.",
//                            "required" : true
//                },
//                "primitive" : {
//                    "type" : "integer",
//                            "description" : "The type of primitives to render.  Allowed values are 0 (POINTS), 1 (LINES), 2 (LINE_LOOP), 3 (LINE_STRIP), 4 (TRIANGLES), 5 (TRIANGLE_STRIP), and 6 (TRIANGLE_FAN).",
//                            "enum" : [0, 1, 2, 3, 4, 5, 6],
//                    "default" : 4
//                }

            std::map<std::string, std::shared_ptr<Accessor>> attributes;
            std::shared_ptr<Accessor>                        indices;
            std::shared_ptr<Material>                        material;
            SceneR::Graphics::PrimitiveType                  type;
        };
    }
}

#endif //MODELMESHPART_HPP
