// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_PROGRAM_HPP
#define SCENER_GRAPHICS_OPENGL_PROGRAM_HPP

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <string>

namespace SceneR { namespace Graphics { namespace OpenGL {

class ConstantBuffer;
enum class ShaderType : std::uint32_t;

class Shader;

/// Represents an OpenGL program.
class Program final
{
public:
    /// Initializes a new instance of the Program class.
    Program();

    /// Releases all resources being used by this Program instance.
    ~Program() noexcept;

public:
    /// Gets the OpenGL program identifier.
    /// \returns the OpenGL program identifier.
    std::uint32_t id() const noexcept;

    /// Gets the constant buffer assciated with this program.
    /// \returns the constant buffer assciated with this program.
    SceneR::Graphics::OpenGL::ConstantBuffer* constant_buffer() const noexcept;

    /// Activates this program instance.
    void bind() const noexcept;

    /// Attachs the given shader to the program object.
    /// \param shader the shader to be attached to the program object.
    void add_shader(std::shared_ptr<Shader> shader) noexcept;

    /// Deactivates this program instance.
    void unbind() const noexcept;

    /// Links the program object and initializes the constant buffer.
    void link() noexcept;

    /// Gets the uniform offsets.
    /// \returns the uniform offsets.
    std::map<std::string, std::size_t> get_uniform_offsets() const noexcept;

    /// Loads the subroutine at the given index on the given shader stage.
    void activate_subroutine(ShaderType type, std::uint32_t subroutineIndex) const noexcept;

private:
    void create() noexcept;
    void verify_linking_state();

public:
    /// Gets or sets the program name.
    std::string name { };

private:
    std::uint32_t                                             _id              { 0 };
    std::unique_ptr<SceneR::Graphics::OpenGL::ConstantBuffer> _constant_buffer { nullptr };
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_PROGRAM_HPP
