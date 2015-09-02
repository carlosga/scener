#ifndef COMPONENTTYPE_HPP
#define COMPONENTTYPE_HPP

#include <cstdint>

namespace SceneR
{
    namespace GLTF
    {
        enum class ComponentType : std::uint32_t
        {
            Byte          = 5120
          , UnsignedByte  = 5121
          , Short         = 5122
          , UnsignedShort = 5123
          , Float         = 5126
        };
    }
}

#endif //COMPONENTTYPE_HPP
