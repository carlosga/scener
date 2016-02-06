// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_PRIMITIVETYPE_HPP
#define SCENER_GRAPHICS_PRIMITIVETYPE_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Graphics {

/// Defines the primitives types
enum class PrimitiveType : std::uint32_t
{
    point_list = GL_POINTS             ///< Renders the vertices as a collection of isolated points.
                                       ///< This value is unsupported for indexed primitives.
  , line_list  = GL_LINES              ///< Renders the vertices as a list of isolated straight line segments.
                                       ///< Calls that use this primitive type fail if the count is less than two or is odd.
  , line_loop  = GL_LINE_LOOP          ///< Renders a connected group of line segments from the first vertex to the last,
                                       ///< then back to the first. Vertices n and n + 1 define line n.
                                       ///< The last line, however, is defined by vertices N and 1 . N lines are drawn.
  , line_strip = GL_LINE_STRIP         ///< Renders the vertices as a single polyline.
                                       ///< Calls that use this primitive type fail if the count is less than two.
  , triangle_list = GL_TRIANGLES       ///< Renders the specified vertices as a sequence of isolated triangles.
                                       ///< Each group of three vertices defines a separate triangle.
                                       ///< Back face culling is affected by the current winding-order render state.
  , triangle_strip = GL_TRIANGLE_STRIP ///< Renders the vertices as a triangle strip.
                                       ///< The back face culling flag is flipped automatically on even-numbered triangles.
  , triangle_fan = GL_TRIANGLE_FAN     ///< Renders the vertices as a triangle fan.
};

}}

#endif // SCENER_GRAPHICS_PRIMITIVETYPE_HPP
