// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/rasterizer_state.hpp"

namespace scener::graphics
{
    const rasterizer_state rasterizer_state::cull_clockwise         { cull_mode::cull_clockwise_face };
    const rasterizer_state rasterizer_state::cull_counter_clockwise { cull_mode::cull_counter_clockwise_face };
    const rasterizer_state rasterizer_state::cull_none              { cull_mode::none };

    rasterizer_state::rasterizer_state(graphics::cull_mode cull) noexcept
    {
        cull_mode = cull;
    }
}
