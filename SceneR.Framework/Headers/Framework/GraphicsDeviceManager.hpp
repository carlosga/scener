// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_GRAPHICSDEVICEMANAGER_HPP
#define FRAMEWORK_GRAPHICSDEVICEMANAGER_HPP

#include <cstdint>
#include <memory>
#include <string>

#include <Framework/IGraphicsDeviceManager.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/GraphicsProfile.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;
    }
}

namespace SceneR
{
    namespace Framework
    {
        class Renderer;

        /**
         * Handles the configuration and management of the graphics device.
         */
        class GraphicsDeviceManager final : public SceneR::Graphics::IGraphicsDeviceService, public IGraphicsDeviceManager
        {
        public:
            /**
             * Initializes a new instance of the GraphicsDeviceManager class
             */
            GraphicsDeviceManager(Renderer& renderer);

            /**
             * Destructor
             */
            ~GraphicsDeviceManager() override;

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
            SceneR::Graphics::GraphicsDevice& graphics_device() const override;

        public:
            /**
             * Gets or sets a value indicating whether to allow the user to resize the device window.
             */
            bool allow_user_resizing;

            /**
             * Gets or sets the graphics profile, which determines the graphics feature set.
             */
            SceneR::Graphics::GraphicsProfile graphics_profile;

            /**
             * Gets or sets the device window title.
             */
            std::u16string window_title;

            /**
             * Gets or sets a value that indicates whether the device should start in full-screen mode.
             */
            bool full_screen;

            /**
             * Gets or sets the preferred back-buffer width.
             */
            std::uint32_t preferred_back_buffer_width;

            /**
             * Gets or sets the preferred back-buffer height.
             * @return the the preferred back-buffer height.
             */
            std::uint32_t preferred_back_buffer_height;

        private:
            std::shared_ptr<SceneR::Graphics::GraphicsDevice> _graphics_device;
            Renderer&                                         _renderer;
        };
    }
}

#endif  // FRAMEWORK_GRAPHICSDEVICEMANAGER_HPP
