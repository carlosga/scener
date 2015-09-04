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
            /**
             * Gets the stencil operation to perform if the stencil test passes and the depth-buffer
             * test fails for a counterclockwise triangle.
             */
            const StencilOperation& CounterClockwiseStencilDepthBufferFail() const;

            /**
             * Sets the stencil operation to perform if the stencil test passes and the depth-buffer
             * test fails for a counterclockwise triangle.
             */
            void CounterClockwiseStencilDepthBufferFail(const StencilOperation& counterClockwiseStencilDepthBufferFail);

            /**
             * Gets the stencil operation to perform if the stencil test fails for a counterclockwise triangle.
             */
            const StencilOperation& CounterClockwiseStencilFail() const;

            /**
             * Sets the stencil operation to perform if the stencil test fails for a counterclockwise triangle.
             */
            void CounterClockwiseStencilFail(const StencilOperation& counterClockwiseStencilFail);

            /**
             * Gets the comparison function to use for counterclockwise stencil tests.
             */
            const CompareFunction& CounterClockwiseStencilFunction() const;

            /**
             * Sets the comparison function to use for counterclockwise stencil tests.
             */
            void CounterClockwiseStencilFunction(const CompareFunction& counterClockwiseStencilFunction);

            /**
             * Gets the stencil operation to perform if the stencil and depth-tests pass for a
             * counterclockwise triangle.
             */
            const StencilOperation& CounterClockwiseStencilPass() const;

            /**
             * Sets the stencil operation to perform if the stencil and depth-tests pass for a
             * counterclockwise triangle.
             */
            void CounterClockwiseStencilPass(const StencilOperation& counterClockwiseStencilPass);

            /**
             * Gets a value indicating where depth buffer is enabled
             */
            bool DepthBufferEnable() const;

            /**
             * Gets a value indicating where depth buffer is enabled
             */
            void DepthBufferEnable(const bool& depthTestEnable);

            /**
             * Gets the comparison function for the depth-buffer test. The default is CompareFunction.LessEqual
             */
            const CompareFunction& DepthBufferFunction() const;

            /**
             * Sets the comparison function for the depth-buffer test. The default is CompareFunction.LessEqual
             */
            void DepthBufferFunction(const CompareFunction& depthBufferFunction);

            /**
             *  Gets a value indicating whether writing to the depth buffer is allowed. The default is true.
             */
            bool DepthBufferWriteEnable() const;

            /**
             *  Sets a value indicating whether writing to the depth buffer is allowed. The default is true.
             */
            void DepthBufferWriteEnable(const bool& depthBufferWriteEnable);

            /**
             * Specifies a reference value to use for the stencil test.
             */
            std::int32_t ReferenceStencil() const;

            /**
             * Specifies a reference value to use for the stencil test.
             */
            void ReferenceStencil(const std::int32_t& referenceStencil);

            /**
             * Gets the stencil operation to perform if the stencil test passes and
             * the depth-test fails.
             */
            const StencilOperation& StencilDepthBufferFail() const;

            /**
             * Sets the stencil operation to perform if the stencil test passes and
             * the depth-test fails.
             */
            void StencilDepthBufferFail(const StencilOperation& stencilDepthBufferFail);

            /**
             * Gets a value indicating whether the stencil test is enabled.
             */
            bool StencilEnable() const;

            /**
             * Enables or disables the stencil test.
             */
            void StencilEnable(const bool& stencilEnable);

            /**
             * Gets the stencil operation to perform if the stencil test fails.
             */
            const StencilOperation& StencilFail() const;

            /**
             * Sets the stencil operation to perform if the stencil test fails.
             */
            void StencilFail(const StencilOperation& stencilFail);

            /**
             * Gets the comparison function for the stencil test.
             */
            const CompareFunction& StencilFunction() const;

            /**
             * Sets the comparison function for the stencil test.
             */
            void StencilFunction(const CompareFunction& stencilFunction);

            /**
             * Gets the mask applied to the reference value and
             * each stencil buffer entry to determine the significant bits
             * for the stencil test.
             */
            std::uint32_t StencilMask() const;

            /**
             * Sets the mask applied to the reference value and
             * each stencil buffer entry to determine the significant bits
             * for the stencil test.
             */
            void StencilMask(const std::uint32_t& stencilMask);

            /**
             * Gets the stencil operation to perform if the stencil test passes
             */
            const StencilOperation& StencilPass() const;

            /**
             * Sets the stencil operation to perform if the stencil test passes
             */
            void StencilPass(const StencilOperation& stencilPass);

            /**
             * Gets the write mask applied to values written into the stencil buffer.
             */
            std::uint32_t StencilWriteMask() const;

            /**
             * Sets the write mask applied to values written into the stencil buffer.
             */
            void StencilWriteMask(const std::uint32_t& stencilWriteMask);

            /**
             * Gets a value indicating wheter two-sided stenciling is enabled.
             */
            bool TwoSidedStencilMode() const;

            /**
             * Enables or disables two-sided stenciling.
             */
            void TwoSidedStencilMode(const bool& twoSidedStencilMode);

        public:
            DepthStencilState& operator=(const DepthStencilState& depthStencilState);

        private:
            void Apply() const;

        private:
            StencilOperation counterClockwiseStencilDepthBufferFail;
            StencilOperation counterClockwiseStencilFail;
            CompareFunction  counterClockwiseStencilFunction;
            StencilOperation counterClockwiseStencilPass;
            bool             depthBufferEnable;
            CompareFunction  depthBufferFunction;
            bool             depthBufferWriteEnable;
            std::int32_t     referenceStencil;
            StencilOperation stencilDepthBufferFail;
            bool             stencilEnable;
            StencilOperation stencilFail;
            CompareFunction  stencilFunction;
            std::uint32_t    stencilMask;
            StencilOperation stencilPass;
            std::uint32_t    stencilWriteMask;
            bool             twoSidedStencilMode;

            friend class SceneR::Framework::GraphicsDeviceManager;
        };
    }
}

#endif  /* DEPTHSTENCILSTATE_HPP */
