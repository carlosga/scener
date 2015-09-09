// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_RENDERERWINDOW_HPP
#define FRAMEWORK_RENDERERWINDOW_HPP

#include <functional>
#include <string>

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
            RendererWindow(Renderer& renderer);

            /**
             * Releases all resource being used by the current RendererWindow
             */
            ~RendererWindow();

        public:
            const std::u16string& title() const;

            /**
             * Sets the renderer window title
             * @param title the renderer window title
             */
            void title(const std::u16string& title);

            /**
             * Specifies whether to allow the user to resize the renderer window.
             * @return whether to allow the user to resize the renderer window.
             */
            bool allow_user_resizing() const;

            /**
             * Specifies whether to allow the user to resize the renderer window.
             */
            void allow_user_resizing(const bool& allowUserResizing);

        private:
            void open();
            void close();
            void initialize_input() const;
            bool should_close() const;
            void enable_debug_output() const;

    #ifdef _USE_GLEW_
            static void debug_callback(GLenum        source
                                     , GLenum        type
                                     , GLuint        id
                                     , GLenum        severity
                                     , GLsizei       length
                                     , const GLchar* message
                                     , void*         userParam);
    #else
            static void debug_callback(GLenum        source
                                     , GLenum        type
                                     , GLuint        id
                                     , GLenum        severity
                                     , GLsizei       length
                                     , const GLchar* message
                                     , const void*   userParam);
    #endif

        private:
            RendererWindow() = delete;
            RendererWindow(const RendererWindow& window) = delete;
            RendererWindow& operator=(const RendererWindow& window) = delete;

        private:
            std::u16string _title;
            GLFWwindow*    _handle;
            Renderer&      _renderer;

            friend class Renderer;
        };
    }
}

#endif  // FRAMEWORK_RENDERERWINDOW_HPP
