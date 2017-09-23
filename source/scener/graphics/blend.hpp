// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_BLEND_HPP
#define SCENER_GRAPHICS_BLEND_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines color blending factors.
    enum class blend : std::uint32_t
    {
        zero                      = 0   ///< Each component of the color is multiplied by (0, 0, 0, 0).
      , one                       = 1   ///< Each component of the color is multiplied by (1, 1, 1, 1).
      , source_color              = 2   ///< Each component of the color is multiplied by the source color.
      , inverse_source_color      = 3   ///< Each component of the color is multiplied by the inverse
                                        ///< of the source color.
      , destination_color         = 4   ///< Each component color is multiplied by the destination color.
      , inverse_destination_color = 5   ///< Each component of the color is multiplied by the inverse
                                        ///< of the destination color.
      , source_alpha              = 6   ///< Each component of the color is multiplied by the alpha
                                        ///< value of the source.
      , inverse_source_alpha      = 7   ///< Each component of the color is multiplied by the inverse
                                        ///< of the alpha value of the source.
      , destination_alpha         = 8   ///< Each component of the color is multiplied by the alpha
                                        ///< value of the destination.
      , inverse_destination_alpha = 9   ///< Each component of the color is multiplied by the inverse
                                        ///< of the alpha value of the destination.
      , blend_factor              = 1   ///< Each component of the color is multiplied by a constant
                                        ///< set in BlendFactor.
      , inverse_blend_factor      = 1   ///< Each component of the color is multiplied by the
                                        ///< inverse of a constant set in BlendFactor.
      , source_alpha_saturation   = 1   ///< Each component of the color is multiplied by either the
                                        ///< alpha of the source color, or the inverse of the alpha of
                                        ///< the source color, whichever is greater.
    };
}

#endif // SCENER_GRAPHICS_BLEND_HPP
