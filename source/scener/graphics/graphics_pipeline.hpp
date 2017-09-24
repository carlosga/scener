// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHICS_PIPELINE_STATES
#define SCENER_GRAPHICS_GRAPHICS_PIPELINE_STATES

#include <vulkan/vulkan.hpp>

#include "scener/graphics/blend_state.hpp"
#include "scener/graphics/depth_stencil_state.hpp"
#include "scener/graphics/rasterizer_state.hpp"
#include "scener/graphics/graphics_resource.hpp"
#include "scener/graphics/effect_technique.hpp"

namespace scener::graphics
{
    class graphics_device;

    class graphics_pipeline final
    {
    public:
        /// Initializes a new instance of the graphics_pipeline class
        /// \param device the graphics device associated with this graphics_pipeline.
        graphics_pipeline(gsl::not_null<graphics_device*> device) noexcept;

    public:
        void set_blend_state(const blend_state&) noexcept;
        void set_depth_stencil_state(const depth_stencil_state&) noexcept;
        void set_rasterizer_state(const rasterizer_state&) noexcept;
        void set_effect_technique(const effect_technique&) noexcept;

        void create() noexcept;

    private:
        graphics_device*    _device;
        blend_state         _blend_state;
        depth_stencil_state _depth_stencil_state;
        rasterizer_state    _rasterizer_state;
        effect_technique    _effect_technique;
        vk::UniquePipeline  _pipeline;
    };
}

#endif
