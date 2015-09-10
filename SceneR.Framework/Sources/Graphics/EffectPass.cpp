// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/EffectPass.hpp>

namespace SceneR
{
    namespace Graphics
    {
        EffectPass::EffectPass()
            : _lighting_model ()
            , _parameters     ()
            , _program        { nullptr }
            , _states         {}
        {
        }

        EffectPass::~EffectPass()
        {
        }

        const std::u16string& EffectPass::name() const
        {
            return _name;
        }

        void EffectPass::apply()
        {
        }
    }
}
