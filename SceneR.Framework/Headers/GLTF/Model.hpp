#ifndef GLTFMODEL_HPP
#define GLTFMODEL_HPP

#include <cstddef>
#include <string>
#include <map>
#include <memory>

#include <GLTF/Buffer.hpp>
#include <GLTF/BufferView.hpp>
#include <GLTF/Accessor.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class Model
        {
        public:
            Model() = default;
            ~Model() = default;

            std::map<std::string, std::shared_ptr<Buffer>>     buffers;
            std::map<std::string, std::shared_ptr<BufferView>> bufferViews;
            std::map<std::string, std::shared_ptr<Accessor>>   accessors;
        };
    }
}

#endif // GLTFMODEL_HPP

