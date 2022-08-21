// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/depth_stencil_state.hpp"

namespace scener::graphics
{
    const depth_stencil_state depth_stencil_state::default_stencil { true, true };
    const depth_stencil_state depth_stencil_state::depth_read      { true, false };
    const depth_stencil_state depth_stencil_state::none            { false, false };

    depth_stencil_state::depth_stencil_state(bool depth_buffer_enabled, bool depth_buffer_write_enabled) noexcept
    {
        depth_buffer_enable       = depth_buffer_enabled;
        depth_buffer_write_enable = depth_buffer_write_enabled;
    }
}
