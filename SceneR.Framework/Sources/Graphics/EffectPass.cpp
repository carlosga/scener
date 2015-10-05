// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/EffectPass.hpp>

#include <Graphics/BlendState.hpp>
#include <Graphics/DepthStencilState.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/RasterizerState.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Graphics::GraphicsDevice;

        EffectPass::EffectPass(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
            : _graphics_device { graphicsDevice }
        {
        }

        const std::string& EffectPass::name() const noexcept
        {
            return _name;
        }

        void EffectPass::begin()
        {
            _program->bind();
        }

        void EffectPass::end()
        {
            _program->unbind();
        }
    }
}
