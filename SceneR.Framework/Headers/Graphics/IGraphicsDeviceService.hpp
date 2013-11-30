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

#ifndef IGRAPHICSDEVICESERVICE_HPP
#define IGRAPHICSDEVICESERVICE_HPP

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;

        /**
         * Defines a mechanism for retrieving GraphicsDevice objects.
         */
        class IGraphicsDeviceService
        {
        protected:
            /**
             * Releases all resources being used by this IGraphicsDeviceService.
             */
            virtual ~IGraphicsDeviceService()
            {
            };

        public:
            /**
             * Retrieves a graphics device.
             */
            virtual GraphicsDevice& CurrentGraphicsDevice() = 0;
        };
    }
}

#endif /* IGRAPHICSDEVICESERVICE_HPP */
