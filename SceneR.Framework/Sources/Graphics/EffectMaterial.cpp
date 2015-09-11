// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/EffectMaterial.hpp>

namespace SceneR
{
    namespace Graphics
    {
        EffectMaterial::EffectMaterial()
        {
        }

        EffectMaterial::~EffectMaterial()
        {
        }

        const std::u16string& EffectMaterial::name() const
        {
            return _name;
        }

        std::shared_ptr<EffectTechnique> EffectMaterial::technique() const
        {
            return _technique;
        }
    }
}

