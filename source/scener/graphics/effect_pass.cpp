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

    const vulkan::graphics_pipeline& effect_pass::pipeline() const noexcept
    {
        return _pipeline;
    }

    const std::shared_ptr<vulkan::shader_module>& effect_pass::shader_module() const noexcept
    {
        return _shader_module;
    }

    const std::vector<std::shared_ptr<effect_parameter>>& effect_pass::parameters() const noexcept
    {
        return _parameters;
    }
}
