// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GLTFMODEL_HPP
#define GLTFMODEL_HPP

#include <cstddef>
#include <string>
#include <map>
#include <memory>

#include <GLTF/Buffer.hpp>
#include <GLTF/BufferView.hpp>
#include <GLTF/Accessor.hpp>
#include <GLTF/Material.hpp>
#include <GLTF/ModelMesh.hpp>
#include <GLTF/Technique.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class Model
        {
        public:
            Model() = default;
            ~Model() = default;

        public:
            std::map<std::string, std::shared_ptr<Buffer>>     buffers;
            std::map<std::string, std::shared_ptr<BufferView>> bufferViews;
            std::map<std::string, std::shared_ptr<Accessor>>   accessors;
            std::map<std::string, std::shared_ptr<Technique>>  techniques;
            std::map<std::string, std::shared_ptr<Material>>   materials;
            std::map<std::string, std::shared_ptr<ModelMesh>>  meshes;
        };
    }
}

#endif // GLTFMODEL_HPP

