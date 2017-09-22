// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_SHADER_MODULE_HPP
#define SCENER_GRAPHICS_SHADER_MODULE_HPP

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <string>

#include "scener/graphics/vulkan/constant_buffer.hpp"
#include "scener/graphics/vulkan/shader.hpp"

namespace scener::graphics::vulkan
{
    /// Represents a Vulkan shader module
    class shader_module final
    {
    public:
        /// Initializes a new instance of the shader_module class.
        shader_module();

    public:
        /// Gets the constant buffer assciated with this shader module.
        /// \returns the constant buffer assciated with this shader module.
        vulkan::constant_buffer* constant_buffer() const noexcept;

        /// Attachs the given shader to the shader module.
        /// \param shader the shader to be attached to the shader module.
        void add_shader(const std::shared_ptr<shader> shader) noexcept;

    public:
        /// Gets the uniform offsets.
        /// \returns the uniform offsets.
        std::map<std::string, std::size_t> query_uniform_offsets() const noexcept;


    public:
        /// Gets or sets the program name.
        std::string name { };

    private:
        std::unique_ptr<vulkan::constant_buffer> _constant_buffer { nullptr };
    };
}

#endif // SCENER_GRAPHICS_OPENGL_PROGRAM_HPP
