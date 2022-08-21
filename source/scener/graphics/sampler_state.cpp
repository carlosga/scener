// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/sampler_state.hpp"

namespace scener::graphics
{
//    const sampler_state sampler_state::anisotropic_clamp { texture_filter::anisotropic, texture_address_mode::clamp };
//    const sampler_state sampler_state::anisotropic_wrap  { texture_filter::anisotropic, texture_address_mode::wrap };
    const sampler_state sampler_state::linear_clamp      { texture_filter::linear     , texture_address_mode::clamp };
    const sampler_state sampler_state::linear_wrap       { texture_filter::linear     , texture_address_mode::wrap };
    const sampler_state sampler_state::point_clamp       { texture_filter::point      , texture_address_mode::clamp };
    const sampler_state sampler_state::point_wrap        { texture_filter::point      , texture_address_mode::wrap };

    sampler_state::sampler_state() noexcept
    {
    }

    sampler_state::sampler_state(texture_filter filter, texture_address_mode address_mode) noexcept
    {
        mag_filter = filter;
        min_filter = filter;
        address_u  = address_mode;
        address_v  = address_mode;
        address_w  = address_mode;
    }
}
