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

#include <System/Core.hpp>
#include <Graphics/CompareFunction.hpp>
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
             * Releases all resources being used by this DepthStencilState
             */
            ~DepthStencilState();

        public:
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
            void DepthBufferFunction(const CompareFunction& depthBufferFunction) const;

            /**
             *  Gets a value indicating whether writing to the depth buffer is allowed. The default is true.
             */
            const System::Boolean& DepthBufferWriteEnable() const;

            /**
             *  Sets a value indicating whether writing to the depth buffer is allowed. The default is true.
             */
            void DepthBufferWriteEnable(const System::Boolean& depthBufferWriteEnable);

        private:
            void Apply() const;

        private:
            System::Boolean depthBufferEnable;
            CompareFunction depthBufferFunction;
            System::Boolean depthBufferWriteEnable;

            friend class SceneR::Framework::GraphicsDeviceManager;
        };
    }
}

#endif  /* DEPTHSTENCILSTATE_HPP */
