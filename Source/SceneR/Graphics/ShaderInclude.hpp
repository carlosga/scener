// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_SHADERINCLUDE_HPP
#define SCENER_GRAPHICS_SHADERINCLUDE_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "SceneR/IDisposable.hpp"

namespace SceneR { namespace Graphics {

struct ShaderInclude : public SceneR::IDisposable
{
public:
    ShaderInclude(const std::string&               name
                , const std::string&               path
                , const std::vector<std::uint8_t>& source) noexcept;

    ShaderInclude(const std::string& name, const std::string& path, const std::string& source) noexcept;

    virtual ~ShaderInclude() override = default;

public:
    virtual void dispose() noexcept override;

public:
    void declare() const noexcept;

    void remove() const noexcept;

    bool is_declared() const noexcept;

public:
    const std::string name;
    const std::string path;
    const std::string source;
};

}}

#endif // SCENER_GRAPHICS_SHADERINCLUDE_HPP
