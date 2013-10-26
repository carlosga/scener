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

#ifndef IGRAPHICSDEVICEMANAGER_HPP
#define IGRAPHICSDEVICEMANAGER_HPP

#include <Framework/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        /**
         * Defines the interface for an object that manages a GraphicsDevice.
         */
        class IGraphicsDeviceManager
        {
        public:
            /**
             * Releases all resources being used by this IGraphicsDeviceManager instance
             */
            virtual ~IGraphicsDeviceManager()
            {
            };

        public:
           /**
             * Starts the drawing of a frame
             */
            virtual Boolean BeginDraw() = 0;

            /**
             * Called to ensure that the device manager has created a valid device.
             */
            virtual void CreateDevice() = 0;

            /**
             * Called by the game at the end of drawing; presents the final rendering.
             */
            virtual void EndDraw() = 0;
        };
    }
}

#endif  /* IGRAPHICSDEVICEMANAGER_HPP */
