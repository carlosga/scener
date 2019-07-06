// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/shader_module.hpp"

#include <gsl/gsl>

namespace scener::graphics::vulkan
{
    const std::vector<std::shared_ptr<shader>>& shader_module::shaders() const noexcept
    {
        return _shaders;
    }    
}
