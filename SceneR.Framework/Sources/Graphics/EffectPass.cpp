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

        EffectPass::EffectPass(GraphicsDevice& graphicsDevice)
            : _graphics_device { graphicsDevice }
            , _name            ()
            , _lighting_model  ()
            , _parameters      ()
            , _program         { nullptr }
            , _states          { }
        {
        }

        EffectPass::~EffectPass()
        {
        }

        const std::string& EffectPass::name() const
        {
            return _name;
        }

        void EffectPass::apply()
        {
            _program->activate();
        }
    }
}
