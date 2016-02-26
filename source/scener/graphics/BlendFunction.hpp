// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_BLENDFUNCTION_HPP
#define SCENER_GRAPHICS_BLENDFUNCTION_HPP

#include <cstdint>

#include "scener/graphics/opengl/Platform.hpp"

namespace scener { namespace graphics {

/// Defines how to combine a source color with the destination color already on the render target for color blending.
enum class BlendFunction : std::uint32_t
{
    add = GL_FUNC_ADD                           ///< The result is the destination added to the source.
                                                ///< Result = (Source Color * Source Blend) + (Destination Color * Destination Blend)
  , max = GL_MAX                                ///< The result is the maximum of the source and destination.
                                                ///< Result = max((Source Color * Source Blend), (Destination Color * Destination Blend))
  , min = GL_MIN                                ///< The result is the minimum of the source and destination.
                                                ///< Result = min((Source Color * Source Blend), (Destination Color * Destination Blend))
  , reverse_subtract = GL_FUNC_REVERSE_SUBTRACT ///< The result is the source subtracted from the destination.
                                                ///< Result = (Destination Color * Destination Blend) − (Source Color * Source Blend)
  , subtract = GL_FUNC_SUBTRACT                 ///< The result is the destination subtracted from the source.
                                                ///< Result = (Source Color * Source Blend) − (Destination Color * Destination Blend)
};

}}

#endif // SCENER_GRAPHICS_BLENDFUNCTION_HPP
