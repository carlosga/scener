//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef RASTERIZERSTATE_HPP
#define RASTERIZERSTATE_HPP

#include "Core/Core.hpp"
#include "Graphics/CullMode.hpp"
#include "Graphics/FillMode.hpp"
#include "Graphics/GraphicsResource.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Contains rasterizer state, which determines how to convert vector data (shapes) into raster data (pixels).
         */
        class RasterizerState : public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the RasterizerState class.
             */
            RasterizerState(GraphicsDevice& graphicsDevice);

		public:
            /**
             * Specifies the conditions for culling or removing triangles. The default value is CullMode.CounterClockwise.
             */
            const CullMode& GetCullMode() const;

            /**
             * Specifies the conditions for culling or removing triangles. The default value is CullMode.CounterClockwise.
             */
            void SetCullMode(const CullMode& cullMode);

            /**
             * Gets the depth bias for polygons,
             * which is the amount of bias to apply to the depth
             * of a primitive to alleviate depth testing problems for primitives of similar depth. The default value is 0.
             */
            const Single& GetDepthBias() const;

            /**
             * Sets the depth bias for polygons,
             * which is the amount of bias to apply to the depth
             * of a primitive to alleviate depth testing problems for primitives of similar depth. The default value is 0.
             */
            void SetDepthBias(const Single& depthBias);

            /**
             * Gets the fill mode, which defines how a triangle is filled during rendering. The default is FillMode.Solid.
             */
            const FillMode& GetFillMode() const;

            /**
             * Sets the fill mode, which defines how a triangle is filled during rendering. The default is FillMode.Solid.
             */
            void SetFillMode(const FillMode& fillMode);

            /**
             * Enables or disables multisample antialiasing. The default is true.
             */
            const Boolean& GetMultiSampleAntiAlias() const;

            /**
             * Enables or disables multisample antialiasing. The default is true.
             */
            void SetMultiSampleAntiAlias(const Boolean& multiSampleAntiAlias);

            /**
             * Enables or disables scissor testing. The default is false.
             */
            const Boolean& GetScissorTestEnable() const;

            /**
             * Enables or disables scissor testing. The default is false.
             */
            void SetScissorTestEnable(const Boolean& scissorTestEnable);

            /**
             *  Gets a bias value that takes into account the slope of a polygon.
             *  This bias value is applied to coplanar primitives to reduce aliasing
             *  and other rendering artifacts caused by z-fighting. The default is 0.
             */
            const Single& GetSlopeScaleDepthBias() const;

            /**
             *  Gets a bias value that takes into account the slope of a polygon.
             *  This bias value is applied to coplanar primitives to reduce aliasing
             *  and other rendering artifacts caused by z-fighting. The default is 0.
             */
            void SetSlopeScaleDepthBias(const Single& slopeScaleDepthBias);

        private:
            void Apply() const;

        private:
            CullMode cullMode;
            Single   depthBias;
            FillMode fillMode;
            Boolean  multiSampleAntiAlias;
            Boolean  scissorTestEnable;
            Single   slopeScaleDepthBias;

            friend class GraphicsDevice;
        };
    }
}

#endif /* RASTERIZERSTATE_HPP */
