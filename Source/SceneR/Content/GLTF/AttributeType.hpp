// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_GLTF_ATTRIBUTETYPE_HPP
#define SCENER_CONTENT_GLTF_ATTRIBUTETYPE_HPP

#include <cstdint>

namespace SceneR { namespace Content { namespace GLTF {

enum class AttributeType : std::uint32_t
{
    scalar  = 0
  , vector2 = 1
  , vector3 = 2
  , vector4 = 3
  , matrix2 = 4
  , matrix3 = 5
  , matrix4 = 7
};

}}}

#endif // SCENER_CONTENT_GLTF_ATTRIBUTETYPE_HPP
