//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef GRAPHICSDEVICEMANAGER_HPP
#define GRAPHICSDEVICEMANAGER_HPP

#include <Framework/Core.hpp>
#include <Framework/IGraphicsDeviceManager.hpp>
#include <Graphics/GraphicsDevice.hpp>

namespace SceneR
{
    namespace Framework
    {
        class Renderer;

        /**
         * Handles the configuration and management of the graphics device.
         */
        class GraphicsDeviceManager : public IGraphicsDeviceManager
        {
        public:
            /**
             * Initializes a new instance of the GraphicsDeviceManager class
             */
            GraphicsDeviceManager(Renderer& renderer);

            /**
             * Releases all resources being used by this GraphicsDeviceManager instance
             */
            ~GraphicsDeviceManager();

        public:
            /**
             * Applies any changes to device-related propertie.
             */
            void ApplyChanges();

            /**
             * Starts the drawing of a frame.
             */
            virtual Boolean BeginDraw() override;

            /**
             * Creates the graphics device.
             */
            virtual void CreateDevice() override;

            /**
             * Called by the renderer at the end of drawing; presents the final rendering.
             */
            virtual void EndDraw() override;

            /**
             * Gets the graphics device.
             * @return the graphics device.
             */
            SceneR::Graphics::GraphicsDevice& GetGraphicsDevice();

            /**
             * Gets a value indicating whether to allow the user to resize the device window.
             */
            const Boolean GetAllowUserResizing() const;

            /**
             * Geta a value indicating whether to allow the user to resize the device window.
             */
            void SetAllowUserResizing(const Boolean& allowUserResizing);

            /**
             * Gets the window title.
             * @return the window title.
             */
            const std::wstring GetWindowTitle() const;

            /**
             * Sets the window title.
             * @param windowTitle the window title.
             */
            void SetWindowTitle(const std::wstring& windowTitle);

            /**
             * Gets a value that indicates whether the device should start in full-screen mode.
             * @return a value that indicates whether the device should start in full-screen mode.
             */
            const Boolean GetFullScreen();

            /**
             * Sets a value that indicates whether the device should start in full-screen mode.
             */
            void SetFullScreen(const Boolean& fullScreen);

            /**
             * Gets the preferred back-buffer height.
             * @return the the preferred back-buffer height.
             */
            const Size GetPreferredBackBufferHeight();

            /**
             * Sets the preferred back-buffer height.
             */
            void SetPreferredBackBufferHeight(const Size& preferredBackBufferHeight);

            /**
             * Gets the preferred back-buffer width.
             * @return the preferred back-buffer width.
             */
            const Size GetPreferredBackBufferWidth();

            /**
             * Sets the preferred back-buffer width.
             */
            void SetPreferredBackBufferWidth(const Size& preferredBackBufferWidth);

        private:
            Renderer&                        renderer;
            SceneR::Graphics::GraphicsDevice graphicsDevice;

            friend class Renderer;
        };
    }
}

#endif  /* GRAPHICSDEVICEMANAGER_HPP */
