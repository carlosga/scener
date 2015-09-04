// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BUFFERTYPE_HPP
#define BUFFERTYPE_HPP

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

#endif // BUFFERTYPE_HPP
