// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_ATTRIBUTETYPE_HPP
#define SCENER_CONTENT_READERS_ATTRIBUTETYPE_HPP

#include <cstdint>

namespace SceneR
{
    namespace Content
    {
        enum class AttributeType : std::uint8_t
        {
            Scalar  = 0
          , Vector2 = 1
          , Vector3 = 2
          , Vector4 = 3
          , Matrix2 = 4
          , Matrix3 = 5
          , Matrix4 = 7
        };
    }
}

#endif // SCENER_CONTENT_READERS_ATTRIBUTETYPE_HPP
