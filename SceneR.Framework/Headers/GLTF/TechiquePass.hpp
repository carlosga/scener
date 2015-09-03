// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHIQUEPASS_HPP
#define TECHIQUEPASS_HPP

#include <memory>
#include <string>
#include <vector>

#include <GLTF/TechiqueParameter.hpp>
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
            std::string                                      lightingModel;
            std::vector<std::shared_ptr<TechniqueParameter>> parameters;
            TechniquePassStates                              states;
        };
    }
}

#endif // TECHIQUEPASS_HPP
