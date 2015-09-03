#ifndef BUFFERVIEW_HPP
#define BUFFERVIEW_HPP

#include <cstdint>
#include <memory>
#include <string>

#include <Graphics/BufferTarget.hpp>

namespace SceneR
{
    namespace GLTF
    {
        class Buffer;

        class BufferView
        {
        public:
            BufferView() = default;
            ~BufferView() = default;

        public:
            std::shared_ptr<Buffer>        buffer;
            std::uint64_t                  byteOffset;
            std::uint64_t                  byteLength;
            SceneR::Graphics::BufferTarget target;
        };
    }
}

#endif // BUFFERVIEW_HPP
