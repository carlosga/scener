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

namespace scener::content::readers { template <typename T> class content_type_reader; }
namespace scener::graphics::vulkan { class logical_device; }

namespace scener::graphics
{
    class graphics_device;

    class graphics_pipeline final
    {
    public:
        /// Initializes a new instance of the graphics_pipeline class
        /// \param device the graphics device associated with this graphics_pipeline.
        graphics_pipeline(gsl::not_null<graphics_device*> device) noexcept;

    private:
        graphics_device*    _device;
        vk::UniquePipeline  _pipeline;

        template <typename T> friend class scener::content::readers::content_type_reader;
        friend class scener::graphics::vulkan::logical_device;
    };
}

#endif
