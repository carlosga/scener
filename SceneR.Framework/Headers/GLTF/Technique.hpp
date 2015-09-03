// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHNIQUE_HPP
#define TECHNIQUE_HPP

#include <map>
#include <memory>
#include <string>

namespace SceneR
{
    namespace GLTF
    {
        class TechniqueParameter;
        class TechniquePass;

        class Technique
        {
        public:
            Technique() = default;
            ~Technique() = default;

        public:
            std::map<std::string, std::shared_ptr<TechniquePass>>      passes;
            std::map<std::string, std::shared_ptr<TechniqueParameter>> parameters;

            std::shared_ptr<TechniquePass>      pass             = nullptr;
            std::shared_ptr<TechniqueParameter> modelViewMatrix  = nullptr;
            std::shared_ptr<TechniqueParameter> projectionMatrix = nullptr;
            std::shared_ptr<TechniqueParameter> normalMatrix     = nullptr;
            std::shared_ptr<TechniqueParameter> position         = nullptr;
            std::shared_ptr<TechniqueParameter> normal           = nullptr;
            std::shared_ptr<TechniqueParameter> texCoord         = nullptr;
            std::shared_ptr<TechniqueParameter> texBinormal      = nullptr;
            std::shared_ptr<TechniqueParameter> texTangent       = nullptr;
            std::shared_ptr<TechniqueParameter> joint            = nullptr;
            std::shared_ptr<TechniqueParameter> jointMatrix      = nullptr;
            std::shared_ptr<TechniqueParameter> weight           = nullptr;
        };
    }
}

#endif // TECHNIQUE_HPP
