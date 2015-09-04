// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHNIQUEPASSSTATES_HPP
#define TECHNIQUEPASSSTATES_HPP

#include <Graphics/RenderingStateType.hpp>

namespace SceneR
{
    namespace Content
    {
        class TechniquesReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class EffectPassStates
        {
        public:
            EffectPassStates() = default;
            ~EffectPassStates() = default;

        public:
            RenderingStateType enabled;

            friend class SceneR::Content::TechniquesReader;
        };
    }
}

#endif // TECHNIQUEPASSSTATES_HPP
