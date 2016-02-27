// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/component.hpp"

#include "scener/graphics/renderer.hpp"

namespace scener { namespace graphics {

component::component(gsl::not_null<graphics::renderer*> renderer) noexcept
    : _renderer ( renderer )
{
}

graphics::renderer* component::renderer() noexcept
{
    return _renderer;
}

void component::update(const steptime& time) noexcept
{
}

bool component::enabled() const noexcept
{
    return _enabled;
}

void component::enabled(bool enabled) noexcept
{
    _enabled = enabled;
}

std::uint32_t component::update_order() const noexcept
{
    return _update_order;
}

void component::update_order(std::uint32_t order) noexcept
{
    _update_order = order;
}

}}
