// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_RASTERIZER_STATE_HPP
#define SCENER_GRAPHICS_RASTERIZER_STATE_HPP

#include "scener/graphics/cull_mode.hpp"
#include "scener/graphics/fill_mode.hpp"
#include "scener/graphics/graphics_resource.hpp"

namespace scener::graphics
{
    class graphics_device;
    class graphics_device_manager;

    /// Contains rasterizer state, which determines how to convert vector data (shapes) into raster data (pixels).
    class rasterizer_state final : public graphics_resource
    {
    public:
        /// Initializes a new instance of the RasterizerState class.
        /// \param device the graphics device associated with this RasterizerState.
        rasterizer_state(gsl::not_null<graphics_device*> device) noexcept;

        /// Releases all resources being used by this RasterizerState.
        ~rasterizer_state() override = default;

    public:
        /// Specifies the conditions for culling or removing triangles. The default value is CullMode.CullCounterClockwiseFace.
        graphics::cull_mode cull_mode { graphics::cull_mode::cull_counter_clockwise_face };

        /// Gets or sets the depth bias for polygons, which is the amount of bias to apply to the depth
        /// of a primitive to alleviate depth testing problems for primitives of similar depth. The default value is 0.
        float depth_bias { 0.0f };

        /// Gets or sets the fill mode, which defines how a triangle is filled during rendering.
        /// The default value is FillMode.Solid.
        graphics::fill_mode fill_mode { graphics::fill_mode::solid };

        /// Enables or disables multisample antialiasing. The default value is true.
        bool multi_sample_anti_alias { true };

        /// Enables or disables scissor testing. The default value is false.
        bool scissor_test_enable { false };

        /// Gets a bias value that takes into account the slope of a polygon.
        /// This bias value is applied to coplanar primitives to reduce aliasing
        /// and other rendering artifacts caused by z-fighting.
        /// The default value is 0.
        float slope_scale_depth_bias { 0.0f };

    private:
        void apply() const noexcept;

        friend class graphics_device_manager;
    };
}

#endif // SCENER_GRAPHICS_RASTERIZER_STATE_HPP
