// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHNIQUE_HPP
#define TECHNIQUE_HPP

#include <memory>
#include <string>
#include <vector>

#include <GLTF/TechiqueParameter.hpp>
#include <GLTF/TechiquePass.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class Technique
        {
        public:
            Technique() = default;
            ~Technique() = default;

        public:
            std::vector<std::shared_ptr<TechniqueParameter>> parameters;
            std::shared_ptr<TechniquePass>                   pass = nullptr;
            std::vector<std::shared_ptr<TechniquePass>>      passes;

            std::shared_ptr<TechniqueParameter>              modelViewMatrix    = nullptr;
            std::shared_ptr<TechniqueParameter>              projectionMatrix   = nullptr;
            std::shared_ptr<TechniqueParameter>              normalMatrix       = nullptr;
            std::shared_ptr<TechniqueParameter>              position           = nullptr;
            std::shared_ptr<TechniqueParameter>              normal             = nullptr;
            std::shared_ptr<TechniqueParameter>              texCoord           = nullptr;
            std::shared_ptr<TechniqueParameter>              texBinormal        = nullptr;
            std::shared_ptr<TechniqueParameter>              texTangent         = nullptr;
            std::shared_ptr<TechniqueParameter>              joint              = nullptr;
            std::shared_ptr<TechniqueParameter>              jointMatrix        = nullptr;
            std::shared_ptr<TechniqueParameter>              weight             = nullptr;
        };
    }
}

#endif // TECHNIQUE_HPP
