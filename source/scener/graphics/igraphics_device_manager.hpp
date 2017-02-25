// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IGRAPHICS_DEVICE_MANAGER_HPP
#define SCENER_GRAPHICS_IGRAPHICS_DEVICE_MANAGER_HPP

namespace scener::graphics
{
    /// Defines the interface for an object that manages a GraphicsDevice.
    class igraphics_device_manager
    {
    public:
        /// Virtual destructor.
        virtual ~igraphics_device_manager() = default;

    public:
        /// Starts the drawing of a frame
        virtual bool begin_draw() noexcept = 0;

        /// Called to ensure that the device manager has created a valid device.
        virtual void create_device() noexcept = 0;

        /// Called by the game at the end of drawing; presents the final rendering.
        virtual void end_draw() noexcept = 0;
    };
}

#endif // SCENER_GRAPHICS_IGRAPHICS_DEVICE_MANAGER_HPP
