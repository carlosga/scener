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
    : handle(0), title(), renderer(renderer), allowUserResizing(false)
{
}

RendererWindow::~RendererWindow()
{
    this->Close();
}

const UInt32 RendererWindow::GetHandle() const
{
    return this->handle;
}

const std::wstring RendererWindow::GetTitle() const
{
    return this->title;
}

void RendererWindow::SetTitle(const std::wstring& title)
{
    this->title = title;
}

const Boolean RendererWindow::GetAllowUserResizing() const
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
    UInt32                 displayMode    = GLFW_WINDOW;
    
    if (this->renderer.GetGraphicsDevice().GetPresentationParameters().GetFullScreen())
    {
        displayMode = GLFW_FULLSCREEN;
    }

    // Next, we use GLFW to create a window. The window will contain an OpenGL 4.2 core profile context.
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE      , profile);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE    , (this->allowUserResizing ? GL_TRUE : GL_FALSE));
    glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

    this->handle = glfwOpenWindow
    (
        params.GetBackBufferWidth(),  // width
        params.GetBackBufferHeight(), // height
        8,                            // redbits
        8,                            // greenbits
        8,                            // bluebits
        8,                            // alphabits
        24,                           // depthbits
        0,                            // stencilbits
        displayMode                   // mode
    );

    // If glfwOpenWindow is failing for you, then you may need to lower the OpenGL version.
    if (!this->handle)
    {
        throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 4.2");
    }

    // Set window title
    std::string title(this->title.begin(), this->title.end());
    glfwSetWindowTitle(title.c_str());
    
    // Now that we have an OpenGL context available in our window,
    // we initialise GLEW so that we get access to the OpenGL API functions.
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("glewInit failed");
    }

    // We will also use GLEW to double-check that the 4.2 API is available:
    if (!GLEW_VERSION_4_2)
    {
        throw std::runtime_error("OpenGL 4.2 API is not available.");
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
    if (this->handle != 0)
    {
        // Close window
        glfwCloseWindow();

        // Reset object ID
        this->handle = 0;
    }
}
