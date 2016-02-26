// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/EffectPass.hpp"

#include "scener/graphics/GraphicsDevice.hpp"
#include "scener/graphics/opengl/Program.hpp"

namespace scener { namespace graphics {

effect_pass::effect_pass(gsl::not_null<graphics_device*> graphicsDevice) noexcept
    : _graphics_device { graphicsDevice }
{
}

const std::string& effect_pass::name() const noexcept
{
    return _name;
}

void effect_pass::begin() noexcept
{
    _program->bind();
}

void effect_pass::end() noexcept
{
    _program->unbind();
}

}}
