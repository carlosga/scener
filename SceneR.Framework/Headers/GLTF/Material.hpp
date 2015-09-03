// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>
#include <Framework/Vector3.hpp>
#include <GLTF/Technique.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class Material
        {
        public:
            Material() = default;
            ~Material() = default;

        public:
            std::shared_ptr<Technique> instanceTechnique;

            std::string                ambient;
            std::string                bump;
            std::string                diffuse;
            SceneR::Framework::Vector3 emission;
            float                      shininess;
            SceneR::Framework::Vector3 specular;
        };
    }
}

#endif // MATERIAL_HPP
