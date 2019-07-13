// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_PRIMITIVE_TYPE_HPP
#define SCENER_GRAPHICS_PRIMITIVE_TYPE_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines the primitives types
    enum class primitive_type : std::uint32_t
    {
        point_list     = 0x0000  ///< Renders the vertices as a collection of isolated points.
                                 ///< This value is unsupported for indexed primitives.
      , line_list      = 0x0001  ///< Renders the vertices as a list of isolated straight line segments.
                                 ///< Calls that use this primitive type fail if the count is less than two or is odd.
      , line_loop      = 0x0002  ///< Renders a connected group of line segments from the first vertex to the last,
                                 ///< then back to the first. Vertices n and n + 1 define line n.
                                 ///< The last line, however, is defined by vertices N and 1 . N lines are drawn.

      , line_strip     = 0x0003  ///< Renders the vertices as a single polyline.
                                 ///< Calls that use this primitive type fail if the count is less than two.
      , triangle_list  = 0x0004  ///< Renders the specified vertices as a sequence of isolated triangles.
                                 ///< Each group of three vertices defines a separate triangle.
                                 ///< Back face culling is affected by the current winding-order render state.
      , triangle_strip = 0x0005  ///< Renders the vertices as a triangle strip.
                                 ///< The back face culling flag is flipped automatically on even-numbered triangles.
      , triangle_fan   = 0x0006  ///< Renders the vertices as a triangle fan.
    };
}

#endif // SCENER_GRAPHICS_PRIMITIVE_TYPE_HPP
