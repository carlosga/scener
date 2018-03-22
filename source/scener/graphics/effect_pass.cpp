// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/effect_pass.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/vulkan/shader.hpp"

namespace scener::graphics
{
    const std::string& effect_pass::name() const noexcept
    {
        return _name;
    }

    const vk::Pipeline& effect_pass::pipeline() const noexcept
    {
        return _pipeline.get();
    }

    const std::vector<std::shared_ptr<vulkan::shader>>& effect_pass::shaders() const noexcept
    {
        return _shaders;
    }
}
