// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_CULLMODE_HPP
#define SCENER_GRAPHICS_CULLMODE_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Graphics {

/// Defines winding orders that may be used for face culling.
enum class CullMode : std::uint32_t
{
    cull_clockwise_face         = GL_CW     ///< Cull back faces with clockwise vertices.
  , cull_counter_clockwise_face = GL_CCW    ///< Cull front faces with counterclockwise vertices.
  , none                        = 0         ///< Do not perform culling
};

}}

#endif // SCENER_GRAPHICS_CULLMODE_HPP
