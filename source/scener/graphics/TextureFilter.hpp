// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_TEXTUREFILTER_HPP
#define SCENER_GRAPHICS_TEXTUREFILTER_HPP

#include <cstdint>

namespace scener { namespace graphics {

/// Defines filtering types during texture sampling.
enum class texture_filter : std::uint32_t
{
    nearest                = 9728   ///< GL_NEAREST
  , linear                 = 9729   ///< GL_LINEAR
  , nearest_mipmap_nearest = 9984   ///< GL_NEAREST_MIPMAP_NEAREST
  , linear_mipmap_nearest  = 9985   ///< GL_LINEAR_MIPMAP_NEAREST
  , nearest_mipmap_linear  = 9986   ///< GL_NEAREST_MIPMAP_LINEAR
  , linear_mipmap_linear   = 9987   ///< GL_LINEAR_MIPMAP_LINEAR
};

}}

#endif // SCENER_GRAPHICS_TEXTUREFILTER_HPP
