// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_IGRAPHICSDEVICESERVICE_HPP
#define GRAPHICS_IGRAPHICSDEVICESERVICE_HPP

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
        public:
            /**
             * Destructor
             */
            virtual ~IGraphicsDeviceService();

        public:
            /**
             * Retrieves a graphics device.
             */
            virtual GraphicsDevice& graphics_device() const = 0;
        };
    }
}

#endif  // GRAPHICS_IGRAPHICSDEVICESERVICE_HPP
