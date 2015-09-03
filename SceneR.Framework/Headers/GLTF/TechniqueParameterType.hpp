// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TECHNIQUEPARAMETERTYPE_HPP
#define TECHNIQUEPARAMETERTYPE_HPP

#include <cstdint>

namespace SceneR
{
    namespace GLTF
    {
        enum class TechniqueParameterType : std::uint32_t
        {
            Byte          = 5120
          , UnsignedByte  = 5121
          , Short         = 5122
          , UnsignedShort = 5123
          , Int           = 5124
          , UnsignedInt   = 5125
          , Float         = 5126
          , Vector2Float  = 35664
          , Vector3Float  = 35665
          , Vector4Float  = 35666
          , Vector2Int    = 35667
          , Vector3Int    = 35668
          , Vector4Int    = 35669
          , Bool          = 35670
          , Vector2Bool   = 35671
          , Vector3Bool   = 35672
          , Vector4Bool   = 35673
          , Matrix2Float  = 35674
          , Matrix3Float  = 35675
          , Matrix4Float  = 35676
          , Sampler2D     = 35678
        };
    }
}

#endif // TECHNIQUEPARAMETERTYPE_HPP
