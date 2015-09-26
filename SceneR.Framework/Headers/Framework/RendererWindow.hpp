// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_RENDERERWINDOW_HPP
#define FRAMEWORK_RENDERERWINDOW_HPP

#include <string>

#include <gsl.h>

#include <System/Graphics/Platform.hpp>

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
            RendererWindow(Guide::not_null<Renderer*> renderer);

            /**
             * Releases all resource being used by the current RendererWindow
             */
            ~RendererWindow();

        public:
            /**
             * Gets the renderer window title.
             */
            const std::string& title() const noexcept;

            /**
             * Sets the renderer window title.
             * @param title the renderer window title.
             */
            void title(const std::string& title) noexcept;

            /**
             * Specifies whether to allow the user to resize the renderer window.
             * @return whether to allow the user to resize the renderer window.
             */
            bool allow_user_resizing() const noexcept;

            /**
             * Specifies whether to allow the user to resize the renderer window.
             */
            void allow_user_resizing(const bool& allowUserResizing) noexcept;

        private:
            void open();
            void close() noexcept;
            void initialize_input() const noexcept;
            bool should_close() const noexcept;

            static void debug_callback(GLenum        source
                                     , GLenum        type
                                     , GLuint        id
                                     , GLenum        severity
                                     , GLsizei       length
                                     , const GLchar* message
                                     , const void*   userParam) noexcept;

            void enable_debug_output() const noexcept;

        private:
            RendererWindow() = delete;
            RendererWindow(const RendererWindow& window) = delete;
            RendererWindow& operator=(const RendererWindow& window) = delete;

        private:
            std::string _title    = { };
            GLFWwindow* _handle   = nullptr;
            Renderer*   _renderer = nullptr;

            friend class Renderer;
        };
    }
}

#endif  // FRAMEWORK_RENDERERWINDOW_HPP
