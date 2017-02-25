// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/blend_state.hpp"

#include "scener/graphics/graphics_device.hpp"

namespace scener::graphics
{
    blend_state::blend_state(gsl::not_null<graphics_device*> device) noexcept
        : graphics_resource { device }
    {
    }

    void blend_state::apply() const noexcept
    {
        // http://www.opengl.org/wiki/Blending

        auto enabled = !(color_source_blend      == blend::one
                      && color_destination_blend == blend::zero
                      && alpha_source_blend      == blend::one
                      && alpha_destination_blend == blend::zero);

        if (!enabled)
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

        glColorMask((color_write_channels_1 & color_write_channels::red)   == graphics::color_write_channels::red
                  , (color_write_channels_1 & color_write_channels::green) == graphics::color_write_channels::green
                  , (color_write_channels_1 & color_write_channels::blue)  == graphics::color_write_channels::blue
                  , (color_write_channels_1 & color_write_channels::alpha) == graphics::color_write_channels::alpha);

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
