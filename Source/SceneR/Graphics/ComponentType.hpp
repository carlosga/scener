// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_COMPONENTTYPE_HPP
#define SCENER_GRAPHICS_COMPONENTTYPE_HPP

#include <cstdint>

namespace SceneR { namespace Graphics {

enum class ComponentType : std::uint32_t
{
    Byte   = 5120
  , UByte  = 5121
  , Int16  = 5122
  , UInt16 = 5123
  , Single = 5126
};

}}

#endif // SCENER_GRAPHICS_COMPONENTTYPE_HPP
