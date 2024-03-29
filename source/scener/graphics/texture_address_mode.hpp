// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_TEXTURE_ADDRESS_MODE_HPP
#define SCENER_GRAPHICS_TEXTURE_ADDRESS_MODE_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines modes for addressing texels using texture coordinates that are outside of the typical range of 0.0 to 1.0.
    enum class texture_address_mode : std::uint32_t
    {
        clamp  = 0x812F //< Texture coordinates outside the range [0.0, 1.0] are set to the
                        ///< texture color at 0.0 or 1.0, respectively.
      , mirror = 0x8370 ///< Similar to Wrap, except that the texture is flipped at every integer junction.
                        ///< For u values between 0 and 1, for example, the texture is addressed normally;
                        ///< between 1 and 2, the texture is flipped (mirrored); between 2 and 3,
                        ///< the texture is normal again, and so on.
      , wrap   = 0x2901 ///< Tile the texture at every integer junction. For example, for u values between 0 and 3,
                        ///<  the texture is repeated three times; no mirroring is performed.
    };
}

#endif // SCENER_GRAPHICS_TEXTURE_ADDRESS_MODE_HPP
