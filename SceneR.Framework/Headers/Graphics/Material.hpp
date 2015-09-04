// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>
#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Content
    {
        class MaterialsReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Effect;

        class Material
        {
        public:
            Material() = default;
            ~Material() = default;

        public:
            std::shared_ptr<Effect>    instanceTechnique;
            std::string                ambient;
            std::string                bump;
            std::string                diffuse;
            SceneR::Framework::Vector3 emission;
            float                      shininess;
            SceneR::Framework::Vector3 specular;

            friend class SceneR::Content::MaterialsReader;
        };
    }
}

#endif // MATERIAL_HPP
