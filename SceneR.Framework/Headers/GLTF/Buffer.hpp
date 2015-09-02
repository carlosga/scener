#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstdint>
#include <string>

#include <GLTF/BufferType.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class Buffer
        {
        public:
            Buffer() = default;
            ~Buffer() = default;

        public:
            std::string   uri;
            std::uint64_t byteLength;
            BufferType    type;
        };
    }
}

#endif // BUFFER_HPP
