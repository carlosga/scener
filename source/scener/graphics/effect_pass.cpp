// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/effect_pass.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/vulkan/shader_module.hpp"

namespace scener::graphics
{
    effect_pass::effect_pass(gsl::not_null<graphics_device*> device) noexcept
        : _graphics_device { device }
    {
    }

    const std::string& effect_pass::name() const noexcept
    {
        return _name;
    }

    void effect_pass::begin() noexcept
    {
    }

    void effect_pass::end() noexcept
    {
    }
}
