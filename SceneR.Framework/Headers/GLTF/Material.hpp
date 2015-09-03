// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>
#include <GLTF/MaterialTechnique.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class Material
        {
        public:
            Material();
            ~Material();

        public:
            std::shared_ptr<MaterialTechnique> instanceTechnique;
        };
    }
}

#endif // MATERIAL_HPP
