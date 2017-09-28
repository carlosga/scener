// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/program.hpp"

#include <gsl/gsl>

namespace scener::graphics::vulkan
{
    const std::vector<std::shared_ptr<shader>>& program::shaders() const noexcept
    {
        return _shaders;
    }

    void program::add_shader(const std::shared_ptr<shader>& shader) noexcept
    {
        Ensures(shader.get() != nullptr);

        _shaders.push_back(shader);
    }
}
