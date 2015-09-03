// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MODELMESHPART_HPP
#define MODELMESHPART_HPP

#include <map>
#include <memory>
#include <GLTF/Accessor.hpp>
#include <GLTF/Material.hpp>
#include <Graphics/PrimitiveType.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class ModelMeshPart
        {
        public:
            ModelMeshPart() = default;
            ~ModelMeshPart() = default;

        public:
            std::shared_ptr<Accessor>       joint              = nullptr;
            std::shared_ptr<Accessor>       normal             = nullptr;
            std::shared_ptr<Accessor>       position           = nullptr;
            std::shared_ptr<Accessor>       textureBinormal    = nullptr;
            std::shared_ptr<Accessor>       textureCoordinates = nullptr;
            std::shared_ptr<Accessor>       textureTangent     = nullptr;
            std::shared_ptr<Accessor>       weight             = nullptr;
            std::shared_ptr<Accessor>       indices            = nullptr;
            std::shared_ptr<Material>       material           = nullptr;
            SceneR::Graphics::PrimitiveType type;
        };
    }
}

#endif //MODELMESHPART_HPP
