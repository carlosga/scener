// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/RendererWindow.hpp>

#include <System/Text/Encoding.hpp>
#include <Framework/GraphicsDeviceManager.hpp>
#include <Framework/Renderer.hpp>
#include <Graphics/GraphicsAdapter.hpp>
#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace System::Text;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

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

const String& RendererWindow::Title() const
{
    return this->title;
}

void RendererWindow::Title(const String& title)
{
    this->title = title;

    if (this->handle != nullptr)
    {
        auto tmp = Encoding::Convert(this->title);

        glfwSetWindowTitle(this->handle, tmp.c_str());
    }
}

const Boolean& RendererWindow::AllowUserResizing() const
{
    return this->allowUserResizing;
}

void RendererWindow::AllowUserResizing(const Boolean& allowUserResizing)
{
    this->allowUserResizing = allowUserResizing;
}

void RendererWindow::Open()
{
    GLFWmonitor* monitor     = nullptr;
    GLFWwindow*  windowShare = nullptr;
    auto         profile     = static_cast<Int32>(this->renderer.graphicsDeviceManager.GraphicsProfile());
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 4);
    glfwWindowHint(GLFW_RESIZABLE             , (allowResize ? GL_TRUE : GL_FALSE));
    glfwWindowHint(GLFW_RED_BITS              , 8);
    glfwWindowHint(GLFW_GREEN_BITS            , 8);
    glfwWindowHint(GLFW_BLUE_BITS             , 8);
    glfwWindowHint(GLFW_ALPHA_BITS            , 8);
    glfwWindowHint(GLFW_DEPTH_BITS            , 24);
    glfwWindowHint(GLFW_STENCIL_BITS          , 24);
    glfwWindowHint(GLFW_SAMPLES               , static_cast<Int32>(sampleCount));
    glfwWindowHint(GLFW_SRGB_CAPABLE          , true);

    if (fullscreen)
    {
        monitor = this->renderer.graphicsDeviceManager.CurrentGraphicsDevice().Adapter().MonitorHandle();
    }

    // Create a new window
    this->handle = glfwCreateWindow
    (
        static_cast<Int32>(width)   // width
      , static_cast<Int32>(height)  // height
      , tmp.c_str()                 // title
      , monitor                     // monitor
      , windowShare                 // share
    );

    // If glfwCreateWindow is failing for you, then you may need to lower the OpenGL version.
    if (!this->handle)
    {
        throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 4.3");
    }

    // Set the new window context as the current context
    glfwMakeContextCurrent(this->handle);

    // Disable regal emulation as it prevents the shaders to be compiled correctly
    glDisable(GL_EMULATION_REGAL);

    // Initialize input
    this->InitializeInput();
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
    // Enable sticky keys
    glfwSetInputMode(this->handle, GLFW_STICKY_KEYS, GL_TRUE);

    // Enable mouse cursor (only needed for fullscreen mode)
    glfwSetInputMode(this->handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool RendererWindow::ShouldClose() const
{
    auto fullScreen = this->renderer.CurrentGraphicsDevice().PresentationParameters().FullScreen();

    return ((!fullScreen && glfwGetKey(this->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         || glfwWindowShouldClose(this->handle));
}
