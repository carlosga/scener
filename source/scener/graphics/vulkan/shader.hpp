// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_SHADER_HPP
#define SCENER_GRAPHICS_VULKAN_SHADER_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <vulkan/vulkan.hpp>

#include "scener/graphics/vulkan/shader_stage.hpp"

namespace scener::graphics::vulkan
{
    /// Represents a shader.
    class shader final
    {
    public:
        /// Initializes a new instance of the Shader class.
        /// \param name the shader name.
        /// \param type the shader stage.
        /// \param buffer the compiled shader contents.
        shader(const std::string& name, shader_stage stage, const std::vector<std::uint8_t>& buffer) noexcept;

    public:
        /// Gets the name of the shader.
        /// \returns the name of the shader.
        const std::string& name() const noexcept;

        /// Gets the the shader stage.
        /// \returns the the shader stage.
        shader_stage stage () const noexcept;

        /// Get the shader contents
        /// \returns the shader contents
        const std::vector<std::uint8_t>& buffer() const noexcept;

        vk::ShaderModuleCreateInfo* create_info() noexcept;

    private:
        std::string                _name;
        shader_stage               _stage;
        std::vector<std::uint32_t> _buffer;
        vk::ShaderModuleCreateInfo _create_info;
    };
}

#endif // SCENER_GRAPHICS_VULKAN_SHADER_HPP
