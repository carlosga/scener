// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICSDEVICEMANAGER_HPP
#define GRAPHICSDEVICEMANAGER_HPP

#include <memory>

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
            void Dispose() override;

        public:
            /**
             * Applies any changes to device-related propertie.
             */
            void ApplyChanges();

            /**
             * Starts the drawing of a frame.
             */
            System::Boolean BeginDraw() override;

            /**
             * Called by the renderer at the end of drawing; presents the final rendering.
             */
            void EndDraw() override;

            /**
             * Creates the graphics device.
             */
            void CreateDevice() override;

            /**
             * Gets the graphics device.
             * @return the graphics device.
             */
            SceneR::Graphics::GraphicsDevice& CurrentGraphicsDevice() override;

            /**
             * Gets the graphics profile, which determines the graphics feature set.
             */
            const SceneR::Graphics::GraphicsProfile& GraphicsProfile() const;

            /**
             * Gets the graphics profile, which determines the graphics feature set.
             */
            void GraphicsProfile(const SceneR::Graphics::GraphicsProfile& graphicsProfile);

            /**
             * Gets a value indicating whether to allow the user to reSystem::Size the device window.
             */
            const System::Boolean& AllowUserResizing() const;

            /**
             * Geta a value indicating whether to allow the user to reSystem::Size the device window.
             */
            void AllowUserResizing(const System::Boolean& allowUserResizing);

            /**
             * Gets the window title.
             * @return the window title.
             */
            const System::String& WindowTitle() const;

            /**
             * Sets the window title.
             * @param windowTitle the window title.
             */
            void WindowTitle(const System::String& windowTitle);

            /**
             * Gets a value that indicates whether the device should start in full-screen mode.
             * @return a value that indicates whether the device should start in full-screen mode.
             */
            const System::Boolean& FullScreen() const;

            /**
             * Sets a value that indicates whether the device should start in full-screen mode.
             */
            void FullScreen(const System::Boolean& fullScreen);

            /**
             * Gets the preferred back-buffer height.
             * @return the the preferred back-buffer height.
             */
            const System::Size& PreferredBackBufferHeight() const;

            /**
             * Sets the preferred back-buffer height.
             */
            void PreferredBackBufferHeight(const System::Size& preferredBackBufferHeight);

            /**
             * Gets the preferred back-buffer width.
             * @return the preferred back-buffer width.
             */
            const System::Size& PreferredBackBufferWidth() const;

            /**
             * Sets the preferred back-buffer width.
             */
            void PreferredBackBufferWidth(const System::Size& preferredBackBufferWidth);

        private:
            Renderer&                                         renderer;
            std::shared_ptr<SceneR::Graphics::GraphicsDevice> graphicsDevice;
            System::Boolean                                   allowUserResizing;
            System::Boolean                                   fullScreen;
            SceneR::Graphics::GraphicsProfile                 graphicsProfile;
            System::Size                                      preferredBackBufferWidth;
            System::Size                                      preferredBackBufferHeight;
            System::String                                    windowTitle;
        };
    }
}

#endif  /* GRAPHICSDEVICEMANAGER_HPP */
