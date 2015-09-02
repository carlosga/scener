#ifndef ACCESSOR_HPP
#define ACCESSOR_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <GLTF/AttributeType.hpp>
#include <GLTF/ComponentType.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class BufferView;

        class Accessor
        {
        public:
            Accessor() = default;
            ~Accessor() = default;

        public:
            std::shared_ptr<BufferView> bufferView;
            std::uint64_t               byteOffset;
            std::uint8_t                byteStride;
            ComponentType               componentType;
            std::uint64_t               count;
            AttributeType               type;
            std::vector<float>          max;
            std::vector<float>          min;
        };
    }
}

#endif // ACCESSOR_HPP
