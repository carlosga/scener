// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_BLEND_HPP
#define SCENER_GRAPHICS_BLEND_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Graphics {

/**
 * Defines color blending factors.
 */
enum class Blend : std::uint32_t
{
    /**
     * Each component of the color is multiplied by (0, 0, 0, 0).
     */
    zero = GL_ZERO,
    /**
     * Each component of the color is multiplied by (1, 1, 1, 1).
     */
    one = GL_ONE,
    /**
     * Each component of the color is multiplied by the source color.
     */
    source_color = GL_SRC_COLOR,
    /**
     * Each component of the color is multiplied by the inverse of the source color.
     */
    inverse_source_color = GL_ONE_MINUS_SRC_COLOR,
    /**
     * Each component of the color is multiplied by the alpha value of the source.
     */
    source_alpha = GL_SRC_ALPHA,
    /**
     * Each component of the color is multiplied by the inverse of the alpha value of the source.
     */
    inverse_source_alpha = GL_ONE_MINUS_SRC_ALPHA,
    /**
     * Each component of the color is multiplied by the alpha value of the destination.
     */
    destination_alpha = GL_DST_ALPHA,
    /**
     * Each component of the color is multiplied by the inverse of the alpha value of the destination.
     */
    inverse_destination_alpha = GL_ONE_MINUS_DST_ALPHA,
    /**
     * Each component color is multiplied by the destination color.
     */
    destination_color = GL_DST_COLOR,
    /**
     * Each component of the color is multiplied by the inverse of the destination color.
     */
    inverse_destination_color = GL_ONE_MINUS_DST_COLOR,
    /**
     * Each component of the color is multiplied by either the alpha of the source color,
     * or the inverse of the alpha of the source color, whichever is greater.
     */
    source_alpha_saturation = GL_SRC_ALPHA_SATURATE,
    /**
     * Each component of the color is multiplied by a constant set in BlendFactor.
     */
    blend_factor = GL_CONSTANT_COLOR,
    /**
     * Each component of the color is multiplied by the inverse of a constant set in BlendFactor.
     */
    inverse_blend_factor = GL_ONE_MINUS_CONSTANT_COLOR
};

}}

#endif // SCENER_GRAPHICS_BLEND_HPP
