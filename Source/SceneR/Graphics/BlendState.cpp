// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/BlendState.hpp"

#include "SceneR/Graphics/GraphicsDevice.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Math::Color;

BlendState::BlendState(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
    : GraphicsResource { graphicsDevice }
{
}

void BlendState::dispose()
{
}

void BlendState::apply() const
{
    // http://www.opengl.org/wiki/Blending

    auto blendEnabled = !(color_source_blend      == Blend::one
                       && color_destination_blend == Blend::zero
                       && alpha_source_blend      == Blend::one
                       && alpha_destination_blend == Blend::zero);

    if (!blendEnabled)
    {
        glDisable(GL_BLEND);
    }
    else
    {
        glEnable(GL_BLEND);
    }

    glBlendEquationSeparate(static_cast<GLenum>(color_blend_function)
                          , static_cast<GLenum>(alpha_blend_function));

    glBlendFuncSeparate(static_cast<GLenum>(color_source_blend)
                      , static_cast<GLenum>(color_destination_blend)
                      , static_cast<GLenum>(alpha_source_blend)
                      , static_cast<GLenum>(alpha_destination_blend));

    glColorMask((color_write_channels & ColorWriteChannels::red)   == Graphics::ColorWriteChannels::red
              , (color_write_channels & ColorWriteChannels::green) == Graphics::ColorWriteChannels::green
              , (color_write_channels & ColorWriteChannels::blue)  == Graphics::ColorWriteChannels::blue
              , (color_write_channels & ColorWriteChannels::alpha) == Graphics::ColorWriteChannels::alpha);

    glBlendColor(blend_factor.r / 255
               , blend_factor.g / 255
               , blend_factor.b / 255
               , blend_factor.a / 255);

    if (multi_sample_mask != 0)
    {
        glSampleCoverage(multi_sample_mask, GL_FALSE);
    }
}

}}
