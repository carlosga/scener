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

#include <Framework/Renderer.hpp>
#include <Framework/IComponent.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

Renderer::Renderer(const String& rootDirectory)
    : graphicsDeviceManager(*this),
      rendererWindow(*this),
      contentManager(this->graphicsDeviceManager.GetGraphicsDevice(), rootDirectory),
      components(0)
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
    this->LoadContent();
    this->StartEventLoop();
    this->UnloadContent();
    this->EndRun();
}

void Renderer::Exit()
{
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

std::vector<std::shared_ptr<IComponent>>& Renderer::Components()
{
    return this->components;
}

bool Renderer::BeginDraw()
{
    return true;
}

void Renderer::BeginRun()
{
    this->rendererWindow.Open();
}

void Renderer::Draw()
{
}

void Renderer::EndDraw()
{
    this->rendererWindow.SwapBuffers();
}

void Renderer::EndRun()
{
}

void Renderer::Finalize()
{
}

void Renderer::Initialize()
{
    this->graphicsDeviceManager.ApplyChanges();

    if (this->components.size() > 0)
    {
        for (auto& component : this->components)
        {
            component->Initialize();
        }
    }
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

void Renderer::StartEventLoop()
{
    do
    {
        this->BeginDraw();
        this->Draw();
        this->EndDraw();

        // Check if the ESC key was pressed or the window was closed
    } while (!this->rendererWindow.ShouldClose());
}
