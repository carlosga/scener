// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_COMPAREFUNCTION_HPP
#define SCENER_GRAPHICS_COMPAREFUNCTION_HPP

#include <cstdint>

#include "scener/graphics/opengl/Platform.hpp"

namespace scener { namespace graphics {

/// Specifies the functions used to compare each incoming pixel depth value
/// with the depth value present in the depth buffer.
enum class compare_function : std::uint32_t
{
    always        = GL_ALWAYS   ///< Always passes.
  , equal         = GL_EQUAL    ///< Passes if the incoming depth value is equal to the stored depth value.
  , greater       = GL_GREATER  ///< Passes if the incoming depth value is greater than the stored depth value.
  , greater_equal = GL_GEQUAL   ///< Passes if the incoming depth value is greater than or equal to the stored depth value.
  , less          = GL_LESS     ///< Passes if the incoming depth value is less than the stored depth value.
  , less_equal    = GL_LEQUAL   ///< Passes if the incoming depth value is less than or equal to the stored depth value.
  , never         = GL_NEVER    ///< Never passes.
  , not_equal     = GL_NOTEQUAL ///< Passes if the incoming depth value is not equal to the stored depth value.
};

}}

#endif // SCENER_GRAPHICS_COMPAREFUNCTION_HPP
