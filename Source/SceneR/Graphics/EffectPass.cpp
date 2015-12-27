// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/EffectPass.hpp"

#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Graphics/Program.hpp"

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

        void EffectPass::begin() noexcept
        {
            _program->bind();
        }

        void EffectPass::end() noexcept
        {
            _program->unbind();
        }
    }
}
