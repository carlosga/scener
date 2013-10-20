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

#include "Graphics/Renderer.hpp"
#include "Graphics/RendererWindow.hpp"
#include "Graphics/GraphicsDevice.hpp"

using namespace SceneR::Graphics;

RendererWindow::RendererWindow(Renderer& renderer)
    : title(), renderer(renderer), allowUserResizing(false), window(nullptr)
{
}

RendererWindow::~RendererWindow()
{
    this->Close();
}

GLFWwindow* RendererWindow::GetHandle() const
{
    return this->window;
}

const std::wstring& RendererWindow::GetTitle() const
{
    return this->title;
}

void RendererWindow::SetTitle(const std::wstring& title)
{
    this->title = title;
}

const Boolean& RendererWindow::GetAllowUserResizing() const
{
    return this->allowUserResizing;
}

void RendererWindow::SetAllowUserResizing(const Boolean& allowUserResizing)
{
    this->allowUserResizing = allowUserResizing;            
}

void RendererWindow::Open()
{
    // First, we initialise GLFW.
    if (!glfwInit())
    {
        throw std::runtime_error("glfwInit failed");
    }

    GraphicsDevice         graphicsDevice = this->renderer.GetGraphicsDevice();
    PresentationParameters params         = graphicsDevice.GetPresentationParameters();
    UInt32                 profile        = static_cast<UInt32>(graphicsDevice.GetGraphicsProfile());
    GLFWmonitor*           monitor        = nullptr;

    std::string title(this->title.begin(), this->title.end());

    if (this->renderer.GetGraphicsDevice().GetPresentationParameters().GetFullScreen())
    {
        monitor = glfwGetPrimaryMonitor();
    }

    // Create a new window
    this->window = glfwCreateWindow
    (
        params.GetBackBufferWidth(),    // width
        params.GetBackBufferHeight(),   // height
        title.c_str(),                  // title
        monitor,                        // monitor
        nullptr                         // share
    );

    // Set the new window context as the current context
    glfwMakeContextCurrent(this->window);

    // Set the window and context hints
    glfwWindowHint(GLFW_OPENGL_PROFILE       , profile);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE            , (this->allowUserResizing ? GL_TRUE : GL_FALSE));
    glfwWindowHint(GLFW_CLIENT_API           , GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT , 1);

    // If glfwOpenWindow is failing for you, then you may need to lower the OpenGL version.
    if (!this->window)
    {
        throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 4.3");
    }
    
    // Now that we have an OpenGL context available in our window,
    // we initialise GLEW so that we get access to the OpenGL API functions.
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("glewInit failed");
    }

    // We will also use GLEW to double-check that the 4.3 API is available:
    if (!GLEW_VERSION_4_3)
    {
        throw std::runtime_error("OpenGL 4.3 API is not available.");
    }
    
    // GLEW throws some errors, so discard all the errors so far
    while(glGetError() != GL_NO_ERROR)
    {
    }

    // Enable vertical sync (on cards that support it)
    glfwSwapInterval(1);
}

void RendererWindow::Close()
{
    if (this->window)
    {
        // Close window
        glfwDestroyWindow(this->window);

        // Reset the window pointer
        this->window = nullptr;
    }
}
