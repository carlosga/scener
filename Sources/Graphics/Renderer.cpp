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

#include <iostream>
#include "Graphics/Renderer.hpp"

using namespace SceneR::Content;
using namespace SceneR::Graphics;

Renderer::Renderer(const std::string& rootDirectory)
    : graphicsDeviceManager(*this),
      contentManager(this->graphicsDeviceManager.graphicsDevice, rootDirectory),
      rendererWindow(*this)
{
}

Renderer::~Renderer()
{
    this->Finalize();
    this->Exit();
}

void Renderer::Run()
{
    this->BeginRun();
    this->Initialize();
    this->rendererWindow.Open();
    this->InitializeCallbacks();
    this->graphicsDeviceManager.ApplyChanges();
    this->LoadContent();
    this->StartEventLoop();
    this->UnloadContent();
    this->EndRun();
}

void Renderer::Exit()
{
    this->ReleaseCallbacks();
    this->rendererWindow.Close();
        
    glfwTerminate();
}

GraphicsDevice& Renderer::GetGraphicsDevice()
{
    return this->graphicsDeviceManager.GetGraphicsDevice();
}

RendererWindow& Renderer::GetRendererWindow()
{
    return this->rendererWindow;
}

ContentManager& Renderer::GetContentManager()
{
    return this->contentManager;
}

void Renderer::StartEventLoop()
{
    do
    {
        this->BeginDraw();
        this->Draw();
        this->EndDraw();
                
        // Wait for new events
        glfwWaitEvents();

        // Check if the ESC key was pressed or the window was closed
    } while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));
}

bool Renderer::BeginDraw()
{
    return true;
}

void Renderer::BeginRun()
{
}

void Renderer::Draw()
{
}

void Renderer::EndDraw()
{
    this->graphicsDeviceManager.GetGraphicsDevice().Present();
}

void Renderer::EndRun()
{
}

void Renderer::Finalize()
{
}

void Renderer::Initialize()
{
}

void Renderer::LoadContent()
{
}

void Renderer::UnloadContent()
{
}

void Renderer::Update()
{
}

void Renderer::InitializeCallbacks() const
{
    // Enable sticky keys
    glfwEnable(GLFW_STICKY_KEYS);

    // Enable mouse cursor (only needed for fullscreen mode)
    glfwEnable(GLFW_MOUSE_CURSOR);

    // Disable automatic event polling
    glfwDisable(GLFW_AUTO_POLL_EVENTS);
    
    // Enable debugging output
    // Other OpenGL 4.x debugging functions:
    //     glDebugMessageControl, glDebugMessageInsert, glGetDebugMessageLog.
    glEnable(GL_ARB_debug_output);
    glDebugMessageCallbackARB(Renderer::DebugCallback, nullptr);
    
    /*
    glfwSetWindowSizeCallback(RenderDevice::WindowSizeCallback);
    glfwSetWindowRefreshCallback(RenderDevice::WindowRefreshCallback);
    glfwSetWindowCloseCallback(RenderDevice::WindowCloseCallback);
    glfwSetMousePosCallback(RenderDevice::MousePosCallback);
    glfwSetMouseButtonCallback(RenderDevice::MouseButtonCallback);
    glfwSetKeyCallback(RenderDevice::KeyboardCallback);
    */
}

void Renderer::ReleaseCallbacks() const
{
    glDisable(GL_ARB_debug_output);
    glDebugMessageCallbackARB(nullptr, nullptr);
    /*
    glfwSetWindowSizeCallback(NULL);
    glfwSetWindowRefreshCallback(NULL);
    glfwSetWindowCloseCallback(NULL);
    glfwSetMousePosCallback(NULL);
    glfwSetMouseButtonCallback(NULL);
    */
}

// A debugging callback
void Renderer::DebugCallback(GLenum  source   , GLenum      type,
                             GLuint  id       , GLenum      severity,
                             GLsizei length   , const char* message,
                             void*   userParam)
{
    std::cout << message << std::endl;
}
