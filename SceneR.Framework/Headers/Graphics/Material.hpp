// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>
#include <string>

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
            Material();
            ~Material();

        public:
            const std::u16string& name() const;

        private:
            std::shared_ptr<Effect>    _instanceTechnique;
            std::string                _ambient;
            std::string                _bump;
            std::string                _diffuse;
            SceneR::Framework::Vector3 _emission;
            float                      _shininess;
            SceneR::Framework::Vector3 _specular;
            std::u16string              _name;

            friend class SceneR::Content::MaterialsReader;
        };
    }
}

#endif // MATERIAL_HPP
