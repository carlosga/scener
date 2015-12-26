// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_RASTERIZERSTATE_HPP
#define GRAPHICS_RASTERIZERSTATE_HPP

#include <Graphics/CullMode.hpp>
#include <Graphics/FillMode.hpp>
#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Framework
    {
        class GraphicsDeviceManager;
    }

    namespace Graphics
    {
        class GraphicsDevice;

        /**
         * Contains rasterizer state, which determines how to convert vector data (shapes) into raster data (pixels).
         */
        class RasterizerState final : public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the RasterizerState class.
             */
            RasterizerState(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept;

            /**
             * @brief Copy constructor.
             * @param rasterizerState the rasterizer state to copy from.
             */
            RasterizerState(const RasterizerState& rasterizerState) = default;

            /**
             * Releases all resources being used by this RasterizerState
             */
            virtual ~RasterizerState() override = default;

        public:
            void dispose() override;

        public:
            RasterizerState& operator=(const RasterizerState& rasterizerState) = default;

        private:
            void apply() const;

        public:
            /**
             * Specifies the conditions for culling or removing triangles.
             * The default value is CullMode.CullCounterClockwiseFace.
             */
            CullMode cull_mode { CullMode::CullCounterClockwiseFace };

            /**
             * Gets or sets the depth bias for polygons, which is the amount of bias to apply to the depth
             * of a primitive to alleviate depth testing problems for primitives of similar depth.
             * The default value is 0.
             */
            float depth_bias { 0.0f };

            /**
             * Gets or sets the fill mode, which defines how a triangle is filled during rendering.
             * The default is FillMode.Solid.
             */
            FillMode fill_mode { FillMode::Solid };

            /**
             * Enables or disables multisample antialiasing. The default is true.
             */
            bool multi_sample_anti_alias { true };

            /**
             * Enables or disables scissor testing. The default is false.
             */
            bool scissor_test_enable { false };

            /**
             * Gets a bias value that takes into account the slope of a polygon.
             * This bias value is applied to coplanar primitives to reduce aliasing
             * and other rendering artifacts caused by z-fighting.
             * The default is 0.
             */
            float slope_scale_depth_bias { 0.0f };

            friend class SceneR::Framework::GraphicsDeviceManager;
        };
    }
}

#endif  // GRAPHICS_RASTERIZERSTATE_HPP
