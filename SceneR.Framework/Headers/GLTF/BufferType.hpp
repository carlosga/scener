#ifndef BUFFERTYPE_HPP
#define BUFFERTYPE_HPP

#include <cstdint>

namespace SceneR
{
    namespace GLTF
    {
        enum class BufferType : std::uint8_t
        {
            ArrayBuffer = 0
          , Text        = 1
        };
    }
}

#endif // BUFFERTYPE_HPP
