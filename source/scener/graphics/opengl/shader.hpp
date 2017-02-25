// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_SHADER_HPP
#define SCENER_GRAPHICS_OPENGL_SHADER_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "scener/graphics/opengl/shader_type.hpp"

namespace scener::graphics::opengl
{
    /// Represents a shader.
    class shader final
    {
    public:
        /// Initializes a new instance of the Shader class.
        /// \param name the name of the shader.
        /// \param type the type of the shader.
        /// \param source the source code for the shader.
        shader(const std::string& name, shader_type type, const std::vector<std::uint8_t>& source) noexcept;

        /// Initializes a new instance of the Shader class.
        /// \param name the name of the shader.
        /// \param type the type of the shader.
        /// \param source the source code for the shader.
        shader(const std::string& name, shader_type type, const std::string& source) noexcept;

        /// Releases all resources being used bu this Shader.
        ~shader() noexcept;

    public:
        /// Gets the shader identififer.
        /// \returns the shader identififer.
        std::uint32_t id() const noexcept;

        /// Gets the name of the shader.
        /// \returns the name of the shader.
        const std::string& name() const noexcept;

        /// Gets the type of the shader.
        /// \returns the type of the shader.
        shader_type type() const noexcept;

        /// Performs the compilation of the shader source code.
        void compile() noexcept;

        /// Indicates wheter the shader has been compiled
        bool is_compiled() const noexcept;

    private:
        void verify_compilation_state();

    private:
        std::uint32_t _id;
        shader_type   _type;
        std::string   _name;
        std::string   _source;
    };
}

#endif // SCENER_GRAPHICS_OPENGL_SHADER_HPP
