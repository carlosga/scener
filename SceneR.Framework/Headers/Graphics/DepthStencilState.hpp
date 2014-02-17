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

#ifndef DEPTHSTENCILSTATE_HPP
#define DEPTHSTENCILSTATE_HPP

#include <Graphics/CompareFunction.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <Graphics/StencilOperation.hpp>
#include <System/Core.hpp>

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
             * Releases all resources being used by this DepthStencilState
             */
            virtual ~DepthStencilState() = default;

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
            const System::Boolean& DepthBufferEnable() const;

            /**
             * Gets a value indicating where depth buffer is enabled
             */
            void DepthBufferEnable(const System::Boolean& depthTestEnable);

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
            const System::Boolean& DepthBufferWriteEnable() const;

            /**
             *  Sets a value indicating whether writing to the depth buffer is allowed. The default is true.
             */
            void DepthBufferWriteEnable(const System::Boolean& depthBufferWriteEnable);

            /**
             * Specifies a reference value to use for the stencil test.
             */
            const System::Int32& ReferenceStencil() const;

            /**
             * Specifies a reference value to use for the stencil test.
             */
            void ReferenceStencil(const System::Int32& referenceStencil);

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
            const System::Boolean& StencilEnable() const;

            /**
             * Enables or disables the stencil test.
             */
            void StencilEnable(const System::Boolean& stencilEnable);

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
            const System::Int32& StencilMask() const;

            /**
             * Sets the mask applied to the reference value and
             * each stencil buffer entry to determine the significant bits
             * for the stencil test.
             */
            void StencilMask(const System::Int32& stencilMask);

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
            const System::Int32& StencilWriteMask() const;

            /**
             * Sets the write mask applied to values written into the stencil buffer.
             */
            void StencilWriteMask(const System::Int32& stencilWriteMask);

            /**
             * Gets a value indicating wheter two-sided stenciling is enabled.
             */
            const System::Boolean& TwoSidedStencilMode() const;

            /**
             * Enables or disables two-sided stenciling.
             */
            void TwoSidedStencilMode(const System::Boolean& twoSidedStencilMode);

        private:
            void Apply() const;

        private:
            StencilOperation counterClockwiseStencilDepthBufferFail;
            StencilOperation counterClockwiseStencilFail;
            CompareFunction  counterClockwiseStencilFunction;
            StencilOperation counterClockwiseStencilPass;
            System::Boolean  depthBufferEnable;
            CompareFunction  depthBufferFunction;
            System::Boolean  depthBufferWriteEnable;
            System::Int32    referenceStencil;
            StencilOperation stencilDepthBufferFail;
            System::Boolean  stencilEnable;
            StencilOperation stencilFail;
            CompareFunction  stencilFunction;
            System::Int32    stencilMask;
            StencilOperation stencilPass;
            System::Int32    stencilWriteMask;
            System::Boolean  twoSidedStencilMode;

            friend class SceneR::Framework::GraphicsDeviceManager;
        };
    }
}

#endif  /* DEPTHSTENCILSTATE_HPP */
