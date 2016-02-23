// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Viewport.hpp"

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Graphics {

Viewport::Viewport() noexcept
    : Viewport { 0, 0, 0, 0 }
{
}

Viewport::Viewport(std::uint32_t vx, std::uint32_t vy, std::uint32_t vwidth, std::uint32_t vheight) noexcept
    : x         { vx }
    , y         { vy }
    , width     { vwidth }
    , height    { vheight }
    , min_depth { 0.0f }
    , max_depth { 1.0f }
{
}

void Viewport::update() const noexcept
{
    glViewportIndexedf(0, x, y, width, height);
    glDepthRangeIndexed(0, min_depth, max_depth);
}

}}
