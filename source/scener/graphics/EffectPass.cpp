// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/EffectPass.hpp"

#include "scener/graphics/GraphicsDevice.hpp"
#include "scener/graphics/opengl/Program.hpp"

namespace scener { namespace graphics {

EffectPass::EffectPass(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
    : _graphics_device { graphicsDevice }
{
}

const std::string& EffectPass::name() const noexcept
{
    return _name;
}

void EffectPass::begin() noexcept
{
    _program->bind();
}

void EffectPass::end() noexcept
{
    _program->unbind();
}

}}
