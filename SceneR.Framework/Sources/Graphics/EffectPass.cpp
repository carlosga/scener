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

        const std::u16string& EffectPass::name() const
        {
            return _name;
        }

        void EffectPass::apply()
        {
            _program->activate();

            /*
            if ((_states.enabled & RenderingStateType::Blend) == RenderingStateType::Blend)
            {
                glEnable(GL_BLEND);
            }
            else
            {
                glDisable(GL_BLEND);
            }
            if ((_states.enabled & RenderingStateType::CullFace) == RenderingStateType::CullFace)
            {
                glEnable(GL_CULL_FACE);
            }
            else
            {
                glDisable(GL_CULL_FACE);
            }
            if ((_states.enabled & RenderingStateType::DepthTest) == RenderingStateType::DepthTest)
            {
                glEnable(GL_DEPTH_TEST);
            }
            else
            {
                glDisable(GL_DEPTH_TEST);
            }
            if ((_states.enabled & RenderingStateType::PolygonOffsetFill) == RenderingStateType::PolygonOffsetFill)
            {
                glEnable(GL_POLYGON_OFFSET_FILL);
            }
            else
            {
                glDisable(GL_POLYGON_OFFSET_FILL);
            }
            if ((_states.enabled & RenderingStateType::SampleAlphaToCoverage) == RenderingStateType::SampleAlphaToCoverage)
            {
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
            }
            else
            {
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
            }
            if ((_states.enabled & RenderingStateType::ScissorTest) == RenderingStateType::ScissorTest)
            {
                glEnable(GL_SCISSOR_TEST);
            }
            else
            {
                glDisable(GL_SCISSOR_TEST);
            }
            */
        }
    }
}
