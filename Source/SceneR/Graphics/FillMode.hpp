// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_FILLMODE_HPP
#define SCENER_GRAPHICS_FILLMODE_HPP

#include <cstdint>

namespace SceneR { namespace Graphics {

/**
 * Describes options for filling the vertices and lines that define a primitive.
 */
enum class FillMode : std::uint32_t
{
    /**
     * draw solid faces for each primitive.
     */
    Solid = 1,
    /**
     * draw lines connecting the vertices that define a primitive face.
     */
    WireFrame = 2
};

}}

#endif // SCENER_GRAPHICS_FILLMODE_HPP
