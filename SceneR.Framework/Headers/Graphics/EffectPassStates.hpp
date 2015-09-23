// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_EFFECTPASSSTATES_HPP
#define GRAPHICS_EFFECTPASSSTATES_HPP

#include <Graphics/RenderingStateType.hpp>

namespace SceneR
{
    namespace Content
    {
        class TechniqueReader;
    }

    namespace Graphics
    {
        class EffectPassStates
        {
        public:
            EffectPassStates() = default;

            ~EffectPassStates() = default;

        public:
            RenderingStateType enabled = RenderingStateType::None;

            friend class SceneR::Content::TechniqueReader;
        };
    }
}

#endif  // GRAPHICS_EFFECTPASSSTATES_HPP
