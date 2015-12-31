// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_GLTF_ATTRIBUTETYPE_HPP
#define SCENER_CONTENT_GLTF_ATTRIBUTETYPE_HPP

#include <cstdint>

namespace SceneR { namespace Content { namespace GLTF {

enum class AttributeType : std::uint32_t
{
    Scalar  = 0
  , Vector2 = 1
  , Vector3 = 2
  , Vector4 = 3
  , Matrix2 = 4
  , Matrix3 = 5
  , Matrix4 = 7
};

}}}

#endif // SCENER_CONTENT_GLTF_ATTRIBUTETYPE_HPP
