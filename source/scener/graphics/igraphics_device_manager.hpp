// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IGRAPHICS_DEVICE_MANAGER_HPP
#define SCENER_GRAPHICS_IGRAPHICS_DEVICE_MANAGER_HPP

#include <nod/nod.hpp>

#include "scener/graphics/graphics_device_information.hpp"

namespace scener::graphics
{
    /// Defines the interface for an object that manages a GraphicsDevice.
    class igraphics_device_manager
    {
    public:
        /// Virtual destructor.
        virtual ~igraphics_device_manager() = default;

    public:
        /// Called to ensure that the device manager has created a valid device.
        virtual void create_device() noexcept = 0;

        /// Starts the preparation phase
        virtual void begin_prepare() noexcept = 0;

        /// Ends the preparation phase
        virtual void end_prepare() noexcept = 0;

        /// Draws the current frame
        virtual void draw() noexcept = 0;

        /// Raised when the graphics_device_manager is changing the graphics_device settings
        /// (during reset or recreation of the GraphicsDevice).
        virtual nod::connection prepare_device_settings(std::function<void(graphics_device_information*)>&& slot) noexcept = 0;
    };
}

#endif // SCENER_GRAPHICS_IGRAPHICS_DEVICE_MANAGER_HPP
