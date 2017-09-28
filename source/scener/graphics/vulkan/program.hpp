// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_PROGRAM_HPP
#define SCENER_GRAPHICS_VULKAN_PROGRAM_HPP

#include <memory>
#include <string>

#include "scener/graphics/vulkan/shader.hpp"

namespace scener::graphics::vulkan
{
    /// Represents a shader program.
    class program final
    {
    public:
        /// Gets the program shaders.
        /// \returns the program shaders.
        const std::vector<std::shared_ptr<shader>>& shaders() const noexcept;

        /// Attachs the given shader to the program object.
        /// \param shader the shader to be attached to the program object.
        void add_shader(const std::shared_ptr<shader>& shader) noexcept;

    public:
        /// Gets or sets the program name.
        std::string name { };

    private:
        std::vector<std::shared_ptr<shader>> _shaders;
    };
}

#endif // SCENER_GRAPHICS_VULKAN_PROGRAM_HPP
