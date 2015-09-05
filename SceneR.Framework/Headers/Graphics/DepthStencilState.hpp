// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef DEPTHSTENCILSTATE_HPP
#define DEPTHSTENCILSTATE_HPP

#include <cstdint>

#include <Graphics/CompareFunction.hpp>
#include <Graphics/StencilOperation.hpp>
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
         * Contains depth-stencil state for the graphics device
         */
        class DepthStencilState : GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the DepthStencilState class
             * with the given GraphcisDevice
             */
            DepthStencilState(GraphicsDevice& graphicsDevice);

            /**
             * Initializes a new instance of the DepthStencilState class. Copy constructor.
             */
            DepthStencilState(const DepthStencilState& depthStencilState);

            /**
             * Releases all resources being used by this DepthStencilState
             */
            ~DepthStencilState();

        public:
            void dispose() override;

        public:
            DepthStencilState& operator=(const DepthStencilState& depthStencilState);

        private:
            void apply() const;

        public:
            /**
             * Gets or sets the stencil operation to perform if the stencil test passes and the depth-buffer
             * test fails for a counterclockwise triangle.
             */
            StencilOperation counter_clockwise_stencil_depth_buffer_fail;

            /**
             * Gets or sets the stencil operation to perform if the stencil test fails for a counterclockwise triangle.
             */
            StencilOperation counter_clockwise_stencil_fail;

            /**
             * Gets or sets the comparison function to use for counterclockwise stencil tests.
             */
            CompareFunction counter_clockwise_stencil_function;

            /**
             * Gets or sets the stencil operation to perform if the stencil and depth-tests pass for a
             * counterclockwise triangle.
             */
            StencilOperation counter_clockwise_stencil_pass;

            /**
             * Gets or sets a value indicating where depth buffer is enabled
             */
            bool depth_buffer_enable;

            /**
             * Gets or sets the comparison function for the depth-buffer test. The default is CompareFunction.LessEqual
             */
            CompareFunction depth_buffer_function;

            /**
             *  Gets or sets a value indicating whether writing to the depth buffer is allowed. The default is true.
             */
            bool depth_buffer_write_enable;

            /**
             * Gets or sets a reference value to use for the stencil test.
             */
            std::int32_t reference_stencil;

            /**
             * Gets or sets the stencil operation to perform if the stencil test passes and
             * the depth-test fails.
             */
            StencilOperation stencil_depth_buffer_fail;

            /**
             * Enables or disables the stencil test.
             */
            bool stencil_enable;

            /**
             * Gets or sets the stencil operation to perform if the stencil test fails.
             */
            StencilOperation stencil_fail;

            /**
             * Gets or sets the comparison function for the stencil test.
             */
            CompareFunction stencil_function;

            /**
             * Gets or sets the mask applied to the reference value and
             * each stencil buffer entry to determine the significant bits
             * for the stencil test.
             */
            std::uint32_t stencil_mask;

            /**
             * Gets or sets the stencil operation to perform if the stencil test passes
             */
            StencilOperation stencil_pass;

            /**
             * Gets or sets the write mask applied to values written into the stencil buffer.
             */
            std::uint32_t stencil_write_mask;

            /**
             * Enables or disables two-sided stenciling.
             */
            bool two_sided_stencil_mode;

            friend class SceneR::Framework::GraphicsDeviceManager;
        };
    }
}

#endif  /* DEPTHSTENCILSTATE_HPP */
