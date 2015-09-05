// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef EFFECTPASSINSTANCEPROGRAM_HPP
#define EFFECTPASSINSTANCEPROGRAM_HPP

#include <map>
#include <memory>
#include <string>

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
        class EffectParameter;

        class EffectPassInstanceProgram
        {
        public:
            EffectPassInstanceProgram() = default;
            ~EffectPassInstanceProgram() = default;

        public:
            std::string                                             _name;
            std::map<std::string, std::shared_ptr<EffectParameter>> _attributes;
            std::map<std::string, std::shared_ptr<EffectParameter>> _uniforms;

            friend class SceneR::Content::TechniquesReader;
        };
    }
}

#endif // EFFECTPASSINSTANCEPROGRAM_HPP
