// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/BlendState.hpp>
#include <Graphics/GraphicsDevice.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Color;

        BlendState::BlendState(GraphicsDevice& graphicsDevice)
            : GraphicsResource        { graphicsDevice }
            , alpha_blend_function    { BlendFunction::Add }
            , alpha_destination_blend { Blend::Zero }
            , alpha_source_blend      { Blend::One }
            , blend_factor            { Color::white }
            , color_blend_function    { BlendFunction::Add }
            , color_destination_blend { Blend::Zero }
            , color_source_blend      { Blend::One }
            , color_write_channels    { SceneR::Graphics::ColorWriteChannels::All }
            , color_write_channels_1  { SceneR::Graphics::ColorWriteChannels::All }
            , color_write_channels_2  { SceneR::Graphics::ColorWriteChannels::All }
            , color_write_channels_3  { SceneR::Graphics::ColorWriteChannels::All }
            , multi_sample_mask       { 0 }
        {
        }

        BlendState::BlendState(const BlendState& blendState)
            : GraphicsResource        { blendState._graphics_device }
            , alpha_blend_function    { blendState.alpha_blend_function }
            , alpha_destination_blend { blendState.alpha_destination_blend }
            , alpha_source_blend      { blendState.alpha_source_blend }
            , blend_factor            { blendState.blend_factor }
            , color_blend_function    { blendState.color_blend_function }
            , color_destination_blend { blendState.color_destination_blend }
            , color_source_blend      { blendState.color_source_blend }
            , color_write_channels    { blendState.color_write_channels }
            , color_write_channels_1  { blendState.color_write_channels_1 }
            , color_write_channels_2  { blendState.color_write_channels_2 }
            , color_write_channels_3  { blendState.color_write_channels_3 }
            , multi_sample_mask       { blendState.multi_sample_mask }
        {
        }

        BlendState::~BlendState()
        {
        }

        void BlendState::dispose()
        {
        }

        BlendState&BlendState::operator=(const BlendState& blendState)
        {
            if (this != &blendState)
            {
                _graphics_device        = blendState._graphics_device;
                alpha_blend_function    = blendState.alpha_blend_function;
                alpha_destination_blend = blendState.alpha_destination_blend;
                alpha_source_blend      = blendState.alpha_source_blend;
                blend_factor            = blendState.blend_factor;
                color_blend_function    = blendState.color_blend_function;
                color_destination_blend = blendState.color_destination_blend;
                color_source_blend      = blendState.color_source_blend;
                color_write_channels    = blendState.color_write_channels;
                color_write_channels_1  = blendState.color_write_channels_1;
                color_write_channels_2  = blendState.color_write_channels_2;
                color_write_channels_3  = blendState.color_write_channels_3;
                multi_sample_mask       = blendState.multi_sample_mask;
            }

            return *this;
        }

        void BlendState::apply() const
        {
            // http://www.opengl.org/wiki/Blending

            auto blendEnabled = !(color_source_blend      == Blend::One
                               && color_destination_blend == Blend::Zero
                               && alpha_source_blend      == Blend::One
                               && alpha_destination_blend == Blend::Zero);

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

            glColorMask((color_write_channels & ColorWriteChannels::Red)   == Graphics::ColorWriteChannels::Red
                      , (color_write_channels & ColorWriteChannels::Green) == Graphics::ColorWriteChannels::Green
                      , (color_write_channels & ColorWriteChannels::Blue)  == Graphics::ColorWriteChannels::Blue
                      , (color_write_channels & ColorWriteChannels::Alpha) == Graphics::ColorWriteChannels::Alpha);

            glBlendColor(blend_factor.r / 255
                       , blend_factor.g / 255
                       , blend_factor.b / 255
                       , blend_factor.a / 255);

            if (multi_sample_mask != 0)
            {
                glSampleCoverage(multi_sample_mask, GL_FALSE);
            }
        }
    }
}
