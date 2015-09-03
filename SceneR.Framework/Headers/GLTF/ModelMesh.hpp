// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MODELMESH_HPP
#define MODELMESH_HPP

#include <memory>
#include <vector>
#include <GLTF/ModelMeshPart.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class ModelMesh
        {
        public:
            ModelMesh() = default;
            ~ModelMesh() = default;

        public:
            std::vector<std::shared_ptr<ModelMeshPart>> meshParts;
        };
    }
}

#endif //MODELMESH_HPP
