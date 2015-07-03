// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef RENDERERWINDOW_HPP
#define RENDERERWINDOW_HPP

#include <string>

#include <System/Graphics/Platform.hpp>
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
            const std::u16string& Title() const;

            /**
             * Sets the renderer window title
             * @param title the renderer window title
             */
            void Title(const std::u16string& title);

            /**
             * Specifies whether to allow the user to resize the renderer window.
             * @return whether to allow the user to resize the renderer window.
             */
            bool AllowUserResizing() const;

            /**
             * Specifies whether to allow the user to resize the renderer window.
             */
            void AllowUserResizing(const bool& allowUserResizing);

        private:
            void Open();
            void Close();
            void InitializeInput() const;
            bool ShouldClose() const;
            void EnableDebugOutput() const;
            static void DebugCallback(GLenum        source
                                    , GLenum        type
                                    , GLuint        id
                                    , GLenum        severity
                                    , GLsizei       length
                                    , const GLchar* message
                                    , const void*   userParam);

        private:
            RendererWindow() = delete;
            RendererWindow(const RendererWindow& window) = delete;
            RendererWindow& operator=(const RendererWindow& window) = delete;

        private:
            std::u16string title;
            bool           allowUserResizing;
            GLFWwindow*    handle;
            Renderer&      renderer;

            friend class Renderer;
        };
    }
}

#endif  /* RENDERERWINDOW_HPP */
