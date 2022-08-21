// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/blend_state.hpp"

namespace scener::graphics
{
    const blend_state blend_state::additive          { blend::source_alpha, blend::one };
    const blend_state blend_state::alpha_blend       { blend::one         , blend::inverse_source_alpha };
    const blend_state blend_state::non_premultiplied { blend::source_alpha, blend::inverse_source_alpha };
    const blend_state blend_state::opaque            { blend::one         , blend::zero };

    blend_state::blend_state(blend source_blend, blend destination_blend) noexcept
    {
        color_source_blend      = source_blend;
        alpha_source_blend      = source_blend;
        color_destination_blend = destination_blend;
        alpha_destination_blend = destination_blend;
    }
}
