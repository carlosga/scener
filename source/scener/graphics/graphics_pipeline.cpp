// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/graphics_pipeline.hpp"

#include "scener/graphics/graphics_device.hpp"

namespace scener::graphics
{
    graphics_pipeline::graphics_pipeline(gsl::not_null<graphics_device*> device) noexcept
        : graphics_resource    { device }
        , _blend_state         { }
        , _depth_stencil_state { }
        , _rasterizer_state    { }
        , _effect_technique    { device }
    {
    }

    void graphics_pipeline::set_blend_state(const blend_state& state) noexcept
    {
        _blend_state = state;
    }
    void graphics_pipeline::set_depth_stencil_state(const depth_stencil_state& state) noexcept
    {
        _depth_stencil_state = state;
    }
    void graphics_pipeline::set_rasterizer_state(const rasterizer_state& state) noexcept
    {
        _rasterizer_state = state;
    }
    void graphics_pipeline::set_effect_technique(const effect_technique& technique) noexcept
    {
        _effect_technique = technique;
    }

    void graphics_pipeline::create() noexcept
    {
        graphics_resource::device()->create_graphics_pipeline(
            _blend_state
          , _depth_stencil_state
          , _rasterizer_state
          , _effect_technique);
    }
}

