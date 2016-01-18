// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "RasterizerState.hpp"

#include "GraphicsDevice.hpp"

namespace SceneR { namespace Graphics {

RasterizerState::RasterizerState(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
    : GraphicsResource { graphicsDevice }
{
}

void RasterizerState::apply() const noexcept
{
    // Specify whether front- or back-facing facets can be culled
    if (cull_mode == CullMode::none)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glFrontFace(static_cast<GLenum>(cull_mode));

        switch (cull_mode)
        {
            case SceneR::Graphics::CullMode::cull_clockwise_face:
                glCullFace(GL_FRONT);

                break;

            case SceneR::Graphics::CullMode::cull_counter_clockwise_face:
                glCullFace(GL_BACK);
                break;

            default:
                glCullFace(GL_FRONT_AND_BACK);
                break;
        }
    }

    //  Select a polygon rasterization mode
    if (fill_mode == FillMode::solid)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    // Enable or disable the scissor test
    if (scissor_test_enable)
    {
        glEnable(GL_SCISSOR_TEST);
    }
    else
    {
        glDisable(GL_SCISSOR_TEST);
    }

    // set the scale and units used to calculate depth values if needed
    if (depth_bias != 0.0f || slope_scale_depth_bias != 0.0f)
    {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(slope_scale_depth_bias, depth_bias);
    }
    else
    {
        glDisable(GL_POLYGON_OFFSET_FILL);
    }

    // Enable multisample
    if (multi_sample_anti_alias)
    {
        glEnable(GL_MULTISAMPLE);
    }
    else
    {
        glDisable(GL_MULTISAMPLE);
    }
}

}}
