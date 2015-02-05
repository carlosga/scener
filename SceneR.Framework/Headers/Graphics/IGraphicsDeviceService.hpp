// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
            virtual ~IGraphicsDeviceService() = default;

        public:
            /**
             * Retrieves a graphics device.
             */
            virtual GraphicsDevice& CurrentGraphicsDevice() = 0;
        };
    }
}

#endif /* IGRAPHICSDEVICESERVICE_HPP */
