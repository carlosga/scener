// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IGRAPHICSDEVICESERVICE_HPP
#define SCENER_GRAPHICS_IGRAPHICSDEVICESERVICE_HPP

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
            virtual ~IGraphicsDeviceService() = default;

        public:
            /**
             * Retrieves a graphics device.
             */
            virtual GraphicsDevice* graphics_device() const noexcept = 0;
        };
    }
}

#endif  // SCENER_GRAPHICS_IGRAPHICSDEVICESERVICE_HPP
