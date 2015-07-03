// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef RASTERIZERSTATE_HPP
#define RASTERIZERSTATE_HPP

#include <System/Core.hpp>
#include <Graphics/CullMode.hpp>
#include <Graphics/FillMode.hpp>
#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Framework
    {
        class GraphicsDeviceManager;
    }
}

namespace SceneR
{
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
            RasterizerState(GraphicsDevice& graphicsDevice);

            /**
             * @brief Copy constructor.
             * @param rasterizerState the rasterizer state to copy from.
             */
            RasterizerState(const RasterizerState& rasterizerState);

            /**
             * Releases all resources being used by this RasterizerState
             */
            ~RasterizerState() override;

        public:
            void Dispose() override;

        public:
            /**
             * Specifies the conditions for culling or removing triangles.
             * The default value is CullMode.CounterClockwise.
             */
            const SceneR::Graphics::CullMode& CullMode() const;

            /**
             * Specifies the conditions for culling or removing triangles.
             * The default value is CullMode.CounterClockwise.
             */
            void CullMode(const SceneR::Graphics::CullMode& cullMode);

            /**
             * Gets the depth bias for polygons, which is the amount of bias to apply to the depth
             * of a primitive to alleviate depth testing problems for primitives of similar depth.
             * The default value is 0.
             */
            const System::Single& DepthBias() const;

            /**
             * Sets the depth bias for polygons, which is the amount of bias to apply to the depth
             * of a primitive to alleviate depth testing problems for primitives of similar depth.
             * The default value is 0.
             */
            void DepthBias(const System::Single& depthBias);

            /**
             * Gets the fill mode, which defines how a triangle is filled during rendering.
             * The default is FillMode.Solid.
             */
            const SceneR::Graphics::FillMode& FillMode() const;

            /**
             * Sets the fill mode, which defines how a triangle is filled during rendering.
             * The default is FillMode.Solid.
             */
            void FillMode(const SceneR::Graphics::FillMode& fillMode);

            /**
             * Enables or disables multisample antialiasing. The default is true.
             */
            bool MultiSampleAntiAlias() const;

            /**
             * Enables or disables multisample antialiasing. The default is true.
             */
            void MultiSampleAntiAlias(const bool& multiSampleAntiAlias);

            /**
             * Enables or disables scissor testing. The default is false.
             */
            bool ScissorTestEnable() const;

            /**
             * Enables or disables scissor testing. The default is false.
             */
            void ScissorTestEnable(const bool& scissorTestEnable);

            /**
             * Gets a bias value that takes into account the slope of a polygon.
             * This bias value is applied to coplanar primitives to reduce aliasing
             * and other rendering artifacts caused by z-fighting.
             * The default is 0.
             */
            const System::Single& SlopeScaleDepthBias() const;

            /**
             * Gets a bias value that takes into account the slope of a polygon.
             * This bias value is applied to coplanar primitives to reduce aliasing
             * and other rendering artifacts caused by z-fighting.
             * The default is 0.
             */
            void SlopeScaleDepthBias(const System::Single& slopeScaleDepthBias);

        public:
            RasterizerState& operator=(const RasterizerState& rasterizerState);

        private:
            void Apply() const;

        private:
            SceneR::Graphics::CullMode cullMode;
            System::Single             depthBias;
            SceneR::Graphics::FillMode fillMode;
            bool                       multiSampleAntiAlias;
            bool                       scissorTestEnable;
            System::Single             slopeScaleDepthBias;

            friend class SceneR::Framework::GraphicsDeviceManager;
        };
    }
}

#endif  /* RASTERIZERSTATE_HPP */
