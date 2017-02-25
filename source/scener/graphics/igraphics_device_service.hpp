// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IGRAPHICS_DEVICE_SERVICE_HPP
#define SCENER_GRAPHICS_IGRAPHICS_DEVICE_SERVICE_HPP

namespace scener::graphics
{
    class graphics_device;

    /// Defines a mechanism for retrieving GraphicsDevice objects.
    class igraphics_device_service
    {
    public:
        /// Virtual destructor
        virtual ~igraphics_device_service() = default;

    public:
        /// Retrieves a graphics device.
        virtual graphics_device* device() const noexcept = 0;
    };
}

#endif  // SCENER_GRAPHICS_IGRAPHICS_DEVICE_SERVICE_HPP
