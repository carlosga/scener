// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/RendererWindow.hpp>

#include <cstddef>
#include <iostream>

#include <Framework/Renderer.hpp>
#include <Graphics/GraphicsAdapter.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Input/Keyboard.hpp>
#include <Input/KeyboardState.hpp>
#include <Input/Mouse.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Framework
    {
        using SceneR::Input::Keyboard;
        using SceneR::Input::KeyboardState;
        using SceneR::Input::Keys;
        using SceneR::Input::Mouse;
        using System::Text::Encoding;

#ifdef _USE_GLEW_
        void RendererWindow::debug_callback(GLenum        source
                                          , GLenum        type
                                          , GLuint        id
                                          , GLenum        severity
                                          , GLsizei       length
                                          , const GLchar* message
                                          , void*         userParam)
        {
            std::cout << message << std::endl;
        }
#else
        void RendererWindow::debug_callback(GLenum        source
                                          , GLenum        type
                                          , GLuint        id
                                          , GLenum        severity
                                          , GLsizei       length
                                          , const GLchar* message
                                          , const void*   userParam)
        {
            std::cout << message << std::endl;
        }
#endif

        RendererWindow::RendererWindow(Renderer& renderer)
            : _title    {  }
            , _handle   { nullptr }
            , _renderer { renderer }
        {
        }

        RendererWindow::~RendererWindow()
        {
            close();
        }

        const std::u16string& RendererWindow::title() const
        {
            return _title;
        }

        void RendererWindow::title(const std::u16string& title)
        {
            _title = title;

            if (_handle != nullptr)
            {
                auto tmp = Encoding::convert(_title);

                glfwSetWindowTitle(_handle, tmp.c_str());
            }
        }

        bool RendererWindow::allow_user_resizing() const
        {
            return _renderer._graphics_device_manager.allow_user_resizing;
        }

        void RendererWindow::allow_user_resizing(const bool& allowUserResizing)
        {
            _renderer._graphics_device_manager.allow_user_resizing = allowUserResizing;
        }

        void RendererWindow::open()
        {
            GLFWmonitor* monitor     = nullptr;
            GLFWwindow*  windowShare = nullptr;
            auto         profile     = static_cast<std::int32_t>(_renderer._graphics_device_manager.graphics_profile);
            auto         tmp         = System::Text::Encoding::convert(_title);
            auto         fullscreen  = _renderer._graphics_device_manager.full_screen;
            auto         width       = _renderer._graphics_device_manager.preferred_back_buffer_width;
            auto         height      = _renderer._graphics_device_manager.preferred_back_buffer_height;
            auto         allowResize = _renderer._graphics_device_manager.allow_user_resizing;
            auto         sampleCount = _renderer._graphics_device_manager
                                                .graphics_device()
                                                .presentation_parameters()
                                                .multi_sample_count;

            // Set the window and context hints
            glfwWindowHint(GLFW_OPENGL_PROFILE        , profile);
            glfwWindowHint(GLFW_CLIENT_API            , GLFW_OPENGL_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 5);
            glfwWindowHint(GLFW_RESIZABLE             , (allowResize ? GL_TRUE : GL_FALSE));
            glfwWindowHint(GLFW_RED_BITS              , 8);
            glfwWindowHint(GLFW_GREEN_BITS            , 8);
            glfwWindowHint(GLFW_BLUE_BITS             , 8);
            glfwWindowHint(GLFW_ALPHA_BITS            , 8);
            glfwWindowHint(GLFW_DEPTH_BITS            , 24);
            glfwWindowHint(GLFW_STENCIL_BITS          , 24);
            glfwWindowHint(GLFW_SAMPLES               , static_cast<std::int32_t>(sampleCount));
            glfwWindowHint(GLFW_SRGB_CAPABLE          , GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT  , GL_TRUE);

            if (fullscreen)
            {
                monitor = _renderer._graphics_device_manager.graphics_device().adapter().monitor_handle();
            }

            // Create a new window
            _handle = glfwCreateWindow
            (
                static_cast<std::int32_t>(width)    // width
              , static_cast<std::int32_t>(height)   // height
              , tmp.c_str()                         // title
              , monitor                             // monitor
              , windowShare                         // share
            );

            // If glfwCreateWindow is failing for you, then you may need to lower the OpenGL version.
            if (!_handle)
            {
                throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 4.4");
            }

            // Set the new window context as the current context
            glfwMakeContextCurrent(_handle);

#ifdef _USE_GLEW_
            // GLEW Initialization
            glewExperimental = GL_TRUE;

            if (glewInit() != GLEW_OK)
            {
                throw std::runtime_error("glewInit failed");
            }
#else
            // Disable regal emulation as it prevents the shaders to be compiled correctly
            glDisable(GL_EMULATION_REGAL);
#endif
            // initialize input
            initialize_input();

            // Enable debug output
            enable_debug_output();

            if (allowResize)
            {
//                std::function<void(GLFWwindow*, int, int)> _callback
//                        = [](GLFWwindow* window, int width, int height)
//                          {
//                              std::cout << "width: " << width << std::endl;
//                              std::cout << "height: " << height << std::endl;
//                          };

//                auto t  = *_callback.target<void(*)(GLFWwindow*, int, int)>();

//                glfwSetWindowSizeCallback(this->handle, t);
            }
        }

//        void RendererWindow::WindowSizeCallback(GLFWwindow* window, int width, int height)
//        {
//            auto a = 1;
//        }

        void RendererWindow::close()
        {
            if (_handle)
            {
                // Close window
                glfwDestroyWindow(_handle);

                // Reset the window pointer
                _handle = nullptr;
            }
        }

        void RendererWindow::initialize_input() const
        {
            // initialize keyboard input
            Keyboard::initialize(_handle);

            // initialize mouse input
            Mouse::initialize(_handle);
        }

        bool RendererWindow::should_close() const
        {
            auto fullScreen    = _renderer._graphics_device_manager.full_screen;
            auto shouldClose   = glfwWindowShouldClose(_handle);
            auto keyboardState = Keyboard::get_state();
            auto isEscPressed  = keyboardState.is_key_down(Keys::Escape);

            return ((!fullScreen && isEscPressed) || shouldClose);
        }

        void RendererWindow::enable_debug_output() const
        {
            GLuint unusedIds = 0;

            // Enable debugging output
            // Other OpenGL 4.x debugging functions:
            //     glDebugMessageControl, glDebugMessageInsert, glGetDebugMessageLog.
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(RendererWindow::debug_callback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
        }
    }
}
