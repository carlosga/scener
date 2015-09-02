#ifndef BUFFERVIEWTARGET_HPP
#define BUFFERVIEWTARGET_HPP

#include <cstdint>

namespace SceneR
{
    namespace GLTF
    {
        enum class BufferViewTarget : std::uint32_t
        {
            ArrayBuffer        = 34962
          , ElementArrayBuffer = 34963
          , AnimationOrSkin    = 0
        };
    }
}

#endif // BUFFERVIEWTARGET_HPP
