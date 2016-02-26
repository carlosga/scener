// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_GLTF_ATTRIBUTETYPE_HPP
#define SCENER_CONTENT_GLTF_ATTRIBUTETYPE_HPP

#include <cstdint>

namespace scener { namespace content { namespace gltf {

/// Declares the attribute types for GLTF accessors.
enum class attribute_type : std::uint32_t
{
    scalar  = 0 ///< Scalar values.
  , vector2 = 1 ///< Two dimensional vector.
  , vector3 = 2 ///< Three dimensional vector.
  , vector4 = 3 ///< Four dimensional vector.
  , matrix2 = 4 ///< matrix4 2x2
  , matrix3 = 5 ///< matrix4 3x3
  , matrix4 = 7 ///< matrix4 4x4
};

}}}

#endif // SCENER_CONTENT_GLTF_ATTRIBUTETYPE_HPP
