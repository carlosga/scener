// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_BUFFERTYPE_HPP
#define GRAPHICS_BUFFERTYPE_HPP

#include <cstdint>

namespace SceneR
{
    namespace Graphics
    {
        enum class BufferType : std::uint8_t
        {
            ArrayBuffer = 0
          , Text        = 1
        };
    }
}

#endif // GRAPHICS_BUFFERTYPE_HPP
