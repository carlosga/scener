#ifndef ATTRIBUTETYPE_HPP
#define ATTRIBUTETYPE_HPP

#include <cstdint>

namespace SceneR
{
    namespace GLTF
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

#endif // ATTRIBUTETYPE_HPP
