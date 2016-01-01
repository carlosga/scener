// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_PROGRAM_HPP
#define SCENER_GRAPHICS_PROGRAM_HPP

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <string>

#include "SceneR/IDisposable.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL { class ConstantBuffer; } } }

namespace SceneR { namespace Graphics {

enum class ShaderType : std::uint32_t;

class EffectParameter;
class Shader;

class Program final : public SceneR::IDisposable
{
public:
    Program() = default;

    virtual ~Program() override = default;

public:
    virtual void dispose() override;

public:
    std::uint32_t id() const noexcept;

    SceneR::Graphics::OpenGL::ConstantBuffer* constant_buffer() const noexcept;

    void create();

    void bind() const;

    void add_shader(std::shared_ptr<Shader> shader);

    void unbind() const;

    void link();

    std::map<std::string, std::size_t> get_uniform_offsets() const;

    void activate_subroutine(ShaderType type, std::uint32_t subroutineIndex) const;

private:
    void verify_linking_state();

public:
    std::string name { };

private:
    std::uint32_t                                             _id              { 0 };
    std::unique_ptr<SceneR::Graphics::OpenGL::ConstantBuffer> _constant_buffer { nullptr };
};

}}

#endif // SCENER_GRAPHICS_PROGRAM_HPP
