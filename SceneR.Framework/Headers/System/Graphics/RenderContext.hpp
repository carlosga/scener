// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// Based on https://github.com/gamedevtech/X11OpenGLWindow

#ifndef GRAPHICS_OPENGL_X11_GRAPHICS_DEVICE_HPP
#define GRAPHICS_OPENGL_X11_GRAPHICS_DEVICE_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

#include <System/Graphics/Platform.hpp>
#include <System/Graphics/DisplayDevice.hpp>
#include <System/Graphics/DisplaySurface.hpp>

namespace System
{
    namespace Graphics
    {
        class RenderContext final
        {
        public:
            RenderContext(DisplayDevice* display, DisplaySurface* surface)
                : _display(display)
                , _surface(surface)
            {
            }

            ~RenderContext()
            {
                destroy();
            }

        public:
            bool create() noexcept
            {
                // Create GLX OpenGL context
                int context_attribs[] =
                {
                    GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
                    GLX_CONTEXT_MINOR_VERSION_ARB, 5,
                    GLX_CONTEXT_PROFILE_MASK_ARB , GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
                    /*GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,*/
                    0
                };

                _context  = 0;
                const char *glxExts = glXQueryExtensionsString(_display->handle(), _display->screen_id());
                if (!isExtensionSupported(glxExts, "GLX_ARB_create_context"))
                {
                    std::cout << "GLX_ARB_create_context not supported\n";
                    _context = glXCreateNewContext(_display->handle(), _display->frame_buffer_config(), GLX_RGBA_TYPE, 0, true);
                }
                else
                {
                    _context = glXCreateContextAttribsARB(_display->handle(), _display->frame_buffer_config(), 0, true, context_attribs);
                }

                _display->sync();

                // Verifying that context is a direct context
                if (!is_direct_context())
                {
                    std::cout << "Indirect GLX rendering context obtained\n";
                }
                else
                {
                    std::cout << "Direct GLX rendering context obtained\n";
                }

                make_current();

                if (!gladLoadGL())
                {
                    std::cout << "OpenGL 4.5 or greater is required.\n";
                }

                std::cout << "GL Renderer: "  << glGetString(GL_RENDERER) << "\n";
                std::cout << "GL Version: "   << glGetString(GL_VERSION)  << "\n";
                std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

                enable_debug_output();

                return true;
            }

            bool is_direct_context() noexcept
            {
                return (glXIsDirect(_display->handle(), _context));
            }

            void make_current() const noexcept
            {
                glXMakeCurrent(_display->handle(), _surface->handle(), _context);
            }

            void destroy() noexcept
            {
                if (_context && _display)
                {
                    glXDestroyContext(_display->handle(), _context);
                    _context = nullptr;
                }
            }

            void enable_debug_output() const noexcept
            {
                GLuint unusedIds = 0;

                // Enable debugging output
                // Other OpenGL 4.x debugging functions:
                //     glDebugMessageControl, glDebugMessageInsert, glGetDebugMessageLog.
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
                glDebugMessageCallback([] (GLenum        source
                                         , GLenum        type
                                         , GLuint        id
                                         , GLenum        severity
                                         , GLsizei       length
                                         , const GLchar* message
                                         , const void*   userParam) -> void
                                       {
                                           std::cerr << message << std::endl;
                                       }, nullptr);
            }

            void present_interval(std::int32_t interval) const noexcept
            {
                glXSwapIntervalEXT(_display->handle(), _surface->handle(), interval);
            }

            void present() const noexcept
            {
                glXSwapBuffers(_display->handle(), _surface->handle());
            }

        private:
            static bool isExtensionSupported(const std::string& extList, const std::string& extension) noexcept
            {
                return (extList.find(extension) != std::string::npos);
            }

        private:
            DisplayDevice*  _display { nullptr };
            DisplaySurface* _surface { nullptr };
            GLXContext      _context { 0 };
        };
    }
}

#endif // GRAPHICS_OPENGL_X11_GRAPHICS_DEVICE_HPP
