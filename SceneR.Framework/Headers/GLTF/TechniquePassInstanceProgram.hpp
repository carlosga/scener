// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHNIQUEPASSINSTANCEPROGRAM_HPP
#define TECHNIQUEPASSINSTANCEPROGRAM_HPP

#include <map>
#include <memory>
#include <string>

namespace SceneR
{
    namespace GLTF
    {
        class TechniqueParameter;

        class TechniquePassInstanceProgram
        {
        public:
            TechniquePassInstanceProgram() = default;
            ~TechniquePassInstanceProgram() = default;

        public:
            std::string                                                name;
            std::map<std::string, std::shared_ptr<TechniqueParameter>> attributes;
            std::map<std::string, std::shared_ptr<TechniqueParameter>> uniforms;
        };
    }
}

#endif // TECHNIQUEPASSINSTANCEPROGRAM_HPP
