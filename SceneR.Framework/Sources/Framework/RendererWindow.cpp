// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/RendererWindow.hpp>

#include <cstddef>
#include <iostream>

#include <System/Graphics/Platform.hpp>
#include <System/Text/Encoding.hpp>
#include <Framework/Renderer.hpp>
#include <Graphics/GraphicsAdapter.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Input/Keyboard.hpp>
#include <Input/Mouse.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::Text::Encoding;
        using SceneR::Input::Keyboard;
        using SceneR::Input::Mouse;

#ifdef _USE_GLEW_
        void RendererWindow::DebugCallback(GLenum        source
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
    void RendererWindow::DebugCallback(GLenum        source
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
            : title             { u"" }
            , allowUserResizing { false }
            , handle            { nullptr }
            , renderer          ( renderer )
        {
        }

        RendererWindow::~RendererWindow()
        {
            this->Close();
        }

        const std::u16string& RendererWindow::Title() const
        {
            return this->title;
        }

        void RendererWindow::Title(const std::u16string& title)
        {
            this->title = title;

            if (this->handle != nullptr)
            {
                auto tmp = Encoding::Convert(this->title);

                glfwSetWindowTitle(this->handle, tmp.c_str());
            }
        }

        bool RendererWindow::AllowUserResizing() const
        {
            return this->allowUserResizing;
        }

        void RendererWindow::AllowUserResizing(const bool& allowUserResizing)
        {
            this->allowUserResizing = allowUserResizing;
        }

        void RendererWindow::Open()
        {
            GLFWmonitor* monitor     = nullptr;
            GLFWwindow*  windowShare = nullptr;
            auto         profile     = static_cast<std::int32_t>(this->renderer.graphicsDeviceManager.GraphicsProfile());
            auto         tmp         = System::Text::Encoding::Convert(this->title);
            auto         fullscreen  = this->renderer.graphicsDeviceManager.FullScreen();
            auto         width       = this->renderer.graphicsDeviceManager.PreferredBackBufferWidth();
            auto         height      = this->renderer.graphicsDeviceManager.PreferredBackBufferHeight();
            auto         allowResize = this->renderer.graphicsDeviceManager.AllowUserResizing();
            auto         sampleCount = this->renderer.graphicsDeviceManager
                                                     .CurrentGraphicsDevice()
                                                     .PresentationParameters()
                                                     .MultiSampleCount();

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
                monitor = this->renderer.graphicsDeviceManager.CurrentGraphicsDevice().Adapter().MonitorHandle();
            }

            // Create a new window
            this->handle = glfwCreateWindow
            (
                static_cast<std::int32_t>(width)    // width
              , static_cast<std::int32_t>(height)   // height
              , tmp.c_str()                         // title
              , monitor                             // monitor
              , windowShare                         // share
            );

            // If glfwCreateWindow is failing for you, then you may need to lower the OpenGL version.
            if (!this->handle)
            {
                throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 4.4");
            }

            // Set the new window context as the current context
            glfwMakeContextCurrent(this->handle);

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

            // Initialize input
            this->InitializeInput();

            // Enable debug output
            this->EnableDebugOutput();
        }

        void RendererWindow::Close()
        {
            if (this->handle)
            {
                // Close window
                glfwDestroyWindow(this->handle);

                // Reset the window pointer
                this->handle = nullptr;
            }
        }

        void RendererWindow::InitializeInput() const
        {
            // Initialize keyboard input
            Keyboard::Initialize(this->handle);

            // Initialize mouse input
            Mouse::Initialize(this->handle);
        }

        bool RendererWindow::ShouldClose() const
        {
            auto fullScreen = this->renderer.CurrentGraphicsDevice().PresentationParameters().FullScreen();

            return ((!fullScreen && glfwGetKey(this->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                 || glfwWindowShouldClose(this->handle));
        }

        void RendererWindow::EnableDebugOutput() const
        {
            GLuint unusedIds = 0;

            // Enable debugging output
            // Other OpenGL 4.x debugging functions:
            //     glDebugMessageControl, glDebugMessageInsert, glGetDebugMessageLog.
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(RendererWindow::DebugCallback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
        }
    }
}
