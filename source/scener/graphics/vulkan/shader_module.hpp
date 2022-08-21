// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_SHADER_MODULE_HPP
#define SCENER_GRAPHICS_VULKAN_SHADER_MODULE_HPP

#include <memory>
#include <string>

#include "scener/graphics/vulkan/shader.hpp"

namespace scener::content::readers { template <typename T> class content_type_reader; }

namespace scener::graphics::vulkan
{
    /// Represents a shader module.
    class shader_module final
    {
    public:
        /// Gets the program shaders.
        /// \returns the program shaders.
        const std::vector<std::shared_ptr<shader>>& shaders() const noexcept;

    public:
        /// Gets or sets the program name.
        std::string name { };

    private:
        std::vector<std::shared_ptr<shader>> _shaders;

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_GRAPHICS_VULKAN_SHADER_MODULE_HPP
