// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_SHADER_HPP
#define SCENER_GRAPHICS_SHADER_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "SceneR/IDisposable.hpp"
#include "SceneR/Graphics/ShaderType.hpp"

namespace SceneR { namespace Graphics {

struct ShaderInclude;

/**
 * Represents a shader
 */
class Shader final : SceneR::IDisposable
{
public:
    /**
     * Initializes a new instance of the Shader class.
     * @param name the name of the shader.
     * @param type the type of the shader.
     * @param source the source code for the shader.
     */
    Shader(const std::string& name, ShaderType type, const std::vector<std::uint8_t>& source) noexcept;

    /**
     * Initializes a new instance of the Shader class.
     * @param name the name of the shader.
     * @param type the type of the shader.
     * @param source the source code for the shader.
     */
    Shader(const std::string& name, ShaderType type, const std::string& source) noexcept;

    /**
     * Destructor
     */
    ~Shader() override = default;

public:
    void dispose() noexcept override;

public:
    /**
     * Gets the shader identififer.
     */
    std::uint32_t id() const noexcept;

    /**
     * @brief Gets the name of the shader.
     * @return the name of the shader.
     */
    const std::string& name() const noexcept;

    /**
     * @brief Gets the type of the shader.
     * @return the type of the shader.
     */
    ShaderType type() const noexcept;

    /**
     * Adds a shader include reference.
     * @param include the shader include reference.
     */
    void add_include(std::shared_ptr<ShaderInclude> include);

    /**
     * Performs the compilation of the shader source code.
     */
    void compile() noexcept;

    /**
     * Indicates wheter the shader has been compiled
     */
    bool is_compiled() const noexcept;

private:
    void verify_compilation_state();

private:
    std::string                                 _name;
    std::uint32_t                               _id;
    ShaderType                                  _type;
    std::string                                 _source;
    std::vector<std::shared_ptr<ShaderInclude>> _includes;
};

}}

#endif // SCENER_GRAPHICS_SHADER_HPP
