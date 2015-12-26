// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHICSDEVICEMANAGER_HPP
#define SCENER_GRAPHICS_GRAPHICSDEVICEMANAGER_HPP

#include <cstdint>
#include <memory>
#include <string>

#include <gsl.h>

#include <Graphics/IGraphicsDeviceManager.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;
        class Renderer;

        /**
         * Handles the configuration and management of the graphics device.
         */
        class GraphicsDeviceManager final : public IGraphicsDeviceService, public IGraphicsDeviceManager
        {
        public:
            /**
             * Initializes a new instance of the GraphicsDeviceManager class
             */
            GraphicsDeviceManager(gsl::not_null<Renderer*> renderer);

            /**
             * Destructor
             */
            ~GraphicsDeviceManager() = default;

        public:
            void dispose() override;

        public:
            /**
             * Applies any changes to device-related propertie.
             */
            void apply_changes();

            /**
             * Starts the drawing of a frame.
             */
            bool begin_draw() override;

            /**
             * Called by the renderer at the end of drawing; presents the final rendering.
             */
            void end_draw() override;

            /**
             * Creates the graphics device.
             */
            void create_device() override;

            /**
             * Gets the graphics device.
             * @return the graphics device.
             */
            GraphicsDevice* graphics_device() const noexcept override;

        public:
            /**
             * Gets or sets a value indicating whether to allow the user to resize the device window.
             */
            bool allow_user_resizing { false };

            /**
             * Gets or sets the device window title.
             */
            std::string window_title;

            /**
             * Gets or sets a value that indicates whether the device should start in full-screen mode.
             */
            bool full_screen { false };

            /**
             * Gets or sets the preferred back-buffer width.
             */
            std::uint32_t preferred_back_buffer_width { 0 };

            /**
             * Gets or sets the preferred back-buffer height.
             * @return the the preferred back-buffer height.
             */
            std::uint32_t preferred_back_buffer_height { 0 };

       private:
            std::unique_ptr<GraphicsDevice> _graphics_device { nullptr };
            Renderer*                       _renderer        { nullptr };
        };
    }
}

#endif  // SCENER_GRAPHICS_GRAPHICSDEVICEMANAGER_HPP
