// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef RENDERERWINDOW_HPP
#define RENDERERWINDOW_HPP

#include <System/Core.hpp>

struct GLFWwindow;

namespace SceneR
{
    namespace Framework
    {
        class Renderer;

        /**
         * The window associated with a renderer.
         */
        class RendererWindow
        {
        public:
            /**
             * Initializes a new instance of the RendererWindow class.
             * @param renderer the renderer instance owning the renderer window.
             */
            RendererWindow(Renderer& renderer);

            /**
             * Releases all resource being used by the current RendererWindow
             */
            ~RendererWindow();

        public:
            /**
             * Gets the renderer window title
             * @return the renderer window title
             */
            const System::String& Title() const;

            /**
             * Sets the renderer window title
             * @param title the renderer window title
             */
            void Title(const System::String& title);

            /**
             * Specifies whether to allow the user to resize the renderer window.
             * @return whether to allow the user to resize the renderer window.
             */
            const System::Boolean& AllowUserResizing() const;

            /**
             * Specifies whether to allow the user to resize the renderer window.
             */
            void AllowUserResizing(const System::Boolean& allowUserResizing);

        private:
            void Open();
            void Close();
            void InitializeInput() const;
            bool ShouldClose() const;

        private:
            RendererWindow() = delete;
            RendererWindow(const RendererWindow& window) = delete;
            RendererWindow& operator=(const RendererWindow& window) = delete;

        private:
            System::String  title;
            System::Boolean allowUserResizing;
            GLFWwindow*     handle;
            Renderer&       renderer;

            friend class Renderer;
        };
    }
}

#endif  /* RENDERERWINDOW_HPP */
