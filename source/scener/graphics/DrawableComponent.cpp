// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/DrawableComponent.hpp"

#include "scener/graphics/GraphicsDevice.hpp"
#include "scener/graphics/Renderer.hpp"

namespace scener { namespace graphics {

DrawableComponent::DrawableComponent(gsl::not_null<Renderer*> renderer) noexcept
    : Component { renderer }
{
}

GraphicsDevice* DrawableComponent::graphics_device() noexcept
{
    return _renderer->graphics_device();
}

void DrawableComponent::draw(const StepTime& renderTime) noexcept
{
}

bool DrawableComponent::visible() const noexcept
{
    return _visible;
}

void DrawableComponent::visible(bool visible) noexcept
{
    _visible = visible;
}

std::uint32_t DrawableComponent::draw_order() const noexcept
{
    return _draw_order;
}

void DrawableComponent::draw_order(std::uint32_t drawOrder) noexcept
{
    _draw_order = drawOrder;
}

void DrawableComponent::initialize() noexcept
{
    this->load_content();
}

void DrawableComponent::load_content() noexcept
{
}

void DrawableComponent::unload_content() noexcept
{
}

}}
