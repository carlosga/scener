// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_TEXTURE_FILTER_HPP
#define SCENER_GRAPHICS_TEXTURE_FILTER_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines filtering types during texture sampling.
    enum class texture_filter : std::uint32_t
    {
        anisotropic            = 9726   ///< Use anisotropic filtering.
      , point                  = 9727   ///< Use point filtering.
      , linear                 = 9729   ///< Use linear filtering.
      , linear_mipmap_point    = 9985   ///< Use linear filtering to shrink or expand, and point filtering between mipmap levels (mip).
      , point_mipmap_linear    = 9986   ///< Use point filtering to shrink (minify) or expand (magnify), and linear filtering between mipmap levels.
      , linear_mipmap_linear   = 9987   ///<
    };
}

#endif // SCENER_GRAPHICS_TEXTURE_FILTER_HPP
