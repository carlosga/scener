// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/viewport.hpp"

namespace scener::graphics
{
    viewport::viewport() noexcept
        : viewport { 0, 0, 0, 0 }
    {
    }

    viewport::viewport(std::uint32_t vx, std::uint32_t vy, std::uint32_t vwidth, std::uint32_t vheight) noexcept
        : x         { vx }
        , y         { vy }
        , width     { vwidth }
        , height    { vheight }
        , min_depth { 0.0f }
        , max_depth { 1.0f }
    {
    }

    void viewport::update() const noexcept
    {
    }
}
