// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHNIQUEPASSSTATES_HPP
#define TECHNIQUEPASSSTATES_HPP

#include "RenderingStateType.hpp"

namespace SceneR
{
    namespace GLTF
    {
        class TechniquePassStates
        {
        public:
            TechniquePassStates() = default;
            ~TechniquePassStates() = default;

        public:
            RenderingStateType enabled;
        };
    }
}

#endif // TECHNIQUEPASSSTATES_HPP
