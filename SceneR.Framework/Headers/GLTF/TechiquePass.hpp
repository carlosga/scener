// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHIQUEPASS_HPP
#define TECHIQUEPASS_HPP

#include <string>

#include <GLTF/TechniquePassDetails.hpp>
#include <GLTF/TechniquePassInstanceProgram.hpp>
#include <GLTF/TechniquePassStates.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class TechniquePass
        {
        public:
            TechniquePass() = default;
            ~TechniquePass() = default;

        public:
            TechniquePassDetails         details;
            TechniquePassInstanceProgram instanceProgram;
            TechniquePassStates          states;
        };
    }
}

#endif // TECHIQUEPASS_HPP
