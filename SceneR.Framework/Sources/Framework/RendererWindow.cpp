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

#include <Framework/GraphicsDeviceManager.hpp>
#include <Framework/Renderer.hpp>
#include <Framework/RendererWindow.hpp>
#include <Graphics/GraphicsAdapter.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/GraphicsProfile.hpp>
#include <Graphics/PresentationParameters.hpp>
#include <System/Text/Unicode.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

RendererWindow::RendererWindow(Renderer& renderer)
    : title(),
      allowUserResizing(false),
      handle(nullptr),
      renderer(renderer)
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
        std::string tmp = System::Text::Unicode::Narrow(this->title);
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
    auto         gdm         = this->renderer.graphicsDeviceManager;
    auto         profile     = static_cast<UInt32>(gdm.GraphicsProfile());
    auto         tmp         = System::Text::Unicode::Narrow(this->title);
    GLFWmonitor* monitor     = nullptr;
    GLFWwindow*  windowShare = nullptr;

    // Set the window and context hints
    glfwWindowHint(GLFW_OPENGL_PROFILE        , profile);
    glfwWindowHint(GLFW_CLIENT_API            , GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT  , 1);
    glfwWindowHint(GLFW_RESIZABLE             , (gdm.AllowUserResizing() ? GL_TRUE : GL_FALSE));
    glfwWindowHint(GLFW_RED_BITS              , 8);
    glfwWindowHint(GLFW_GREEN_BITS            , 8);
    glfwWindowHint(GLFW_BLUE_BITS             , 8);
    glfwWindowHint(GLFW_ALPHA_BITS            , 8);
    glfwWindowHint(GLFW_DEPTH_BITS            , 24);
    glfwWindowHint(GLFW_STENCIL_BITS          , 8);
    glfwWindowHint(GLFW_SAMPLES               , gdm.CurrentGraphicsDevice().PresentationParameters().MultiSampleCount());
    glfwWindowHint(GLFW_SRGB_CAPABLE          , true);

    if (gdm.FullScreen())
    {
        monitor = gdm.CurrentGraphicsDevice().Adapter().MonitorHandle();
    }

    // Create a new window
    this->handle = glfwCreateWindow
    (
        gdm.PreferredBackBufferWidth(),  // width
        gdm.PreferredBackBufferHeight(), // height
        tmp.c_str(),                     // title
        monitor,                         // monitor
        windowShare                      // share
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

    // Enable debug output
    this->EnableDebugOutput();

    // Initialize input
    this->InitializeInput();
}

void RendererWindow::Close()
{
    if (this->handle)
    {
        // Disable debug output
        this->DisableDebugOutput();

        // Close window
        glfwDestroyWindow(this->handle);

        // Reset the window pointer
        this->handle = nullptr;
    }
}

void RendererWindow::EnableDebugOutput() const
{
    // Enable debugging output
    // Other OpenGL 4.x debugging functions:
    //     glDebugMessageControl, glDebugMessageInsert, glGetDebugMessageLog.
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(RendererWindow::DebugCallback, nullptr);
    GLuint unusedIds = 0;
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
}

void RendererWindow::DisableDebugOutput() const
{
    glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(nullptr, nullptr);
}

void RendererWindow::InitializeInput() const
{
    // Enable sticky keys
    glfwSetInputMode(this->handle, GLFW_STICKY_KEYS, GL_TRUE);

    // Enable mouse cursor (only needed for fullscreen mode)
    glfwSetInputMode(this->handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void RendererWindow::InitializeCallbacks() const
{
    /*
    glfwSetWindowSizeCallback(RenderDevice::WindowSizeCallback);
    glfwSetWindowRefreshCallback(RenderDevice::WindowRefreshCallback);
    glfwSetWindowCloseCallback(RenderDevice::WindowCloseCallback);
    glfwSetMousePosCallback(RenderDevice::MousePosCallback);
    glfwSetMouseButtonCallback(RenderDevice::MouseButtonCallback);
    glfwSetKeyCallback(RenderDevice::KeyboardCallback);
    */
}

void RendererWindow::ReleaseCallbacks() const
{
    /*
    glfwSetWindowSizeCallback(NULL);
    glfwSetWindowRefreshCallback(NULL);
    glfwSetWindowCloseCallback(NULL);
    glfwSetMousePosCallback(NULL);
    glfwSetMouseButtonCallback(NULL);
    */
}

bool RendererWindow::ShouldClose() const
{
    Boolean fullScreen = this->renderer.CurrentGraphicsDevice().PresentationParameters().FullScreen();

    return ((!fullScreen && glfwGetKey(this->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            || glfwWindowShouldClose(this->handle));
}

void RendererWindow::DebugCallback(GLenum  source   , GLenum        type,
                                   GLuint  id       , GLenum        severity,
                                   GLsizei length   , const GLchar* message,
                                   const void* userParam)
{
    std::cout << message << std::endl;
}
