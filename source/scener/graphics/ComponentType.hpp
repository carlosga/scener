// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_COMPONENTTYPE_HPP
#define SCENER_GRAPHICS_COMPONENTTYPE_HPP

#include <cstdint>

namespace scener { namespace graphics {

/// Defines the type of an element of an index buffer or GLTF accessors elements.
enum class ComponentType : std::uint32_t
{
    byte   = 5120   ///< Eight bits (signed)
  , ubyte  = 5121   ///< Eight bits (unsigned)
  , int16  = 5122   ///< Sixteen bits (Signed).
  , uint16 = 5123   ///< Sixteen bits (unsigned).
  , single = 5126   ///< Thirty-two bits (floating point).
};

}}

#endif // SCENER_GRAPHICS_COMPONENTTYPE_HPP
