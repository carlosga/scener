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
        zero                      = 0       ///< Each component of the color is multiplied by (0, 0, 0, 0).
      , one                       = 1       ///< Each component of the color is multiplied by (1, 1, 1, 1).
      , source_color              = 0x0300  ///< Each component of the color is multiplied by the source color.
      , inverse_source_color      = 0x0301  ///< Each component of the color is multiplied by the inverse
                                            ///< of the source color.
      , source_alpha              = 0x0302  ///< Each component of the color is multiplied by the alpha
                                            ///< value of the source.
      , inverse_source_alpha      = 0x0303  ///< Each component of the color is multiplied by the inverse
                                            ///< of the alpha value of the source.
      , destination_alpha         = 0x0304  ///< Each component of the color is multiplied by the alpha
                                            ///< value of the destination.
      , inverse_destination_alpha = 0x0305  ///< Each component of the color is multiplied by the inverse
                                            ///< of the alpha value of the destination.
      , destination_color         = 0x0306  ///< Each component color is multiplied by the destination color.
      , inverse_destination_color = 0x0307  ///< Each component of the color is multiplied by the inverse
                                            ///< of the destination color.
      , source_alpha_saturation   = 0x0308  ///< Each component of the color is multiplied by either the
                                            ///< alpha of the source color, or the inverse of the alpha of
                                            ///< the source color, whichever is greater.
      , blend_factor              = 0x8001  ///< Each component of the color is multiplied by a constant
                                            ///< set in BlendFactor.
      , inverse_blend_factor      = 0x8002  ///< Each component of the color is multiplied by the
                                            ///< inverse of a constant set in BlendFactor.
    };
}

#endif // SCENER_GRAPHICS_BLEND_HPP
