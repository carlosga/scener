// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_MATERIAL_HPP
#define GRAPHICS_MATERIAL_HPP

#include <memory>
#include <string>

#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class EffectTechnique;

        class EffectMaterial
        {
        public:
            EffectMaterial();

            ~EffectMaterial();

        public:
            const std::u16string& name() const;

            std::shared_ptr<EffectTechnique> technique() const;

        private:
            std::u16string                   _name;
            std::shared_ptr<EffectTechnique> _technique;
            std::string                      _ambient;
            std::string                      _bump;
            std::string                      _diffuse;
            SceneR::Framework::Vector3       _emission;
            float                            _shininess;
            SceneR::Framework::Vector3       _specular;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_MATERIAL_HPP
