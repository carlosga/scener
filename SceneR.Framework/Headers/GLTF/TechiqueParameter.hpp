// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHIQUEPARAMETER_HPP
#define TECHIQUEPARAMETER_HPP

#include <cstdint>
#include <string>

#include <GLTF/TechniqueParameterType.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class TechniqueParameter
        {
        public:
            TechniqueParameter() = default;
            ~TechniqueParameter() = default;

        public:
            std::uint32_t         count;
            TechiqueParameterType type;
            std::string           semantic;
            std::string           node;
            std::string           value;
        };
    }
}

#endif // TECHIQUEPARAMETER_HPP
