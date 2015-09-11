// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_EFFECTMATERIAL_HPP
#define GRAPHICS_EFFECTMATERIAL_HPP

#include <memory>
#include <string>

#include <Framework/Vector3.hpp>
#include <Graphics/IEffectMatrices.hpp>

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
        class Texture2D;

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

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_EFFECTMATERIAL_HPP
