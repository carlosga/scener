// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTPASS_HPP
#define EFFECTPASS_HPP

#include <memory>
#include <string>
#include <vector>

#include <Graphics/EffectPassInstanceProgram.hpp>
#include <Graphics/EffectPassStates.hpp>

namespace SceneR
{
    namespace Content
    {
        class TechiquesReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class EffectParameter;

        class EffectPass
        {
        public:
            EffectPass() = default;
            ~EffectPass() = default;

        public:
            std::string                                   lightingModel;
            std::vector<std::shared_ptr<EffectParameter>> parameters;
            EffectPassInstanceProgram                     program;
            EffectPassStates                              states;

            friend class SceneR::Content::TechiquesReader;
        };
    }
}

#endif // EFFECTPASS_HPP
