// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHICS_DEVICE_MANAGER_HPP
#define SCENER_GRAPHICS_GRAPHICS_DEVICE_MANAGER_HPP

#include <cstdint>
#include <memory>
#include <string>

#include <gsl/gsl>

#include "scener/graphics/igraphics_device_manager.hpp"
#include "scener/graphics/igraphics_device_service.hpp"

namespace scener::graphics
{
    class graphics_device;
    class renderer;

    /// Handles the configuration and management of the graphics device.
    class graphics_device_manager final : public igraphics_device_service, public igraphics_device_manager
    {
    public:
        /// Initializes a new instance of the GraphicsDeviceManager class
        /// \param renderer the Renderer associated with this GraphicsDeviceManager.
        graphics_device_manager(gsl::not_null<renderer*> renderer) noexcept;

    public:
        /// Applies any changes to device-related propertie.
        void apply_changes() noexcept;

        /// Starts the drawing of a frame.
        bool begin_draw() noexcept override;

        /// Called by the renderer at the end of drawing; presents the final rendering.
        void end_draw() noexcept override;

        /// Creates the graphics device.
        void create_device() noexcept override;

        /// Gets the graphics device.
        /// \returns the graphics device.
        graphics_device* device() const noexcept override;

    public:
        /// Gets or sets a value indicating whether to allow the user to resize the device window.
        bool allow_user_resizing { false };

        /// Gets or sets the device window title.
        std::string window_title;

        /// Gets or sets a value that indicates whether the device should start in full-screen mode.
        bool full_screen { false };

        /// Gets or sets the preferred back-buffer width.
        std::uint32_t preferred_back_buffer_width { 0 };

        /// Gets or sets the preferred back-buffer height.
        std::uint32_t preferred_back_buffer_height { 0 };

    private:
        std::unique_ptr<graphics_device> _graphics_device { nullptr };
        renderer*                        _renderer        { nullptr };
    };
}

#endif  // SCENER_GRAPHICS_GRAPHICS_DEVICE_MANAGER_HPP
