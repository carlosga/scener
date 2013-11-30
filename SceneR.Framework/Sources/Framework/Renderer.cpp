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

#include <Framework/IComponent.hpp>
#include <Framework/IDrawable.hpp>
#include <Framework/IUpdateable.hpp>
#include <Framework/Renderer.hpp>
#include <Framework/RenderTime.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

Renderer::Renderer(const String& rootDirectory)
    : components(0),
      services(),
      graphicsDeviceManager(*this),
      rendererWindow(*this),
      contentManager(this->services, rootDirectory),
      timer(),
      renderTime(),
      totalRenderTime()
{
}

Renderer::~Renderer()
{
    this->Finalize();
    this->Exit();
}

std::vector<std::shared_ptr<IComponent>>& Renderer::Components()
{
    return this->components;
}

GraphicsDevice& Renderer::CurrentGraphicsDevice()
{
    return this->graphicsDeviceManager.CurrentGraphicsDevice();
}

RendererWindow& Renderer::Window()
{
    return this->rendererWindow;
}

ContentManager& Renderer::Content()
{
    return this->contentManager;
}

RendererServiceContainer& Renderer::Services()
{
    return this->services;
}

void Renderer::Run()
{
    this->BeginRun();
    this->rendererWindow.Open();
    this->graphicsDeviceManager.ApplyChanges();
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

bool Renderer::BeginDraw()
{
    return true;
}

void Renderer::BeginRun()
{
    this->graphicsDeviceManager.CreateDevice();
}

void Renderer::Draw(const RenderTime& renderTime)
{
    for (auto& component : this->components)
    {
        auto drawable = std::dynamic_pointer_cast<IDrawable>(component);

        if (drawable != nullptr && drawable->IsVisible())
        {
            drawable->Draw(renderTime);
        }
    }
}

void Renderer::EndDraw()
{
    this->graphicsDeviceManager.CurrentGraphicsDevice().Present();
}

void Renderer::EndRun()
{
}

void Renderer::Finalize()
{
}

void Renderer::Initialize()
{
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

void Renderer::Update(const RenderTime& renderTime)
{
    for (auto& component : this->components)
    {
        auto updateable = std::dynamic_pointer_cast<IUpdateable>(component);

        if (updateable != nullptr && updateable->IsEnabled())
        {
            updateable->Update(renderTime);
        }
    }
}

void Renderer::StartEventLoop()
{
    do
    {
        this->Tick();

        glfwWaitEvents();
    } while (!this->rendererWindow.ShouldClose());
}

void Renderer::Tick()
{
//    auto elapsed = this->timer.ElapsedTickTime();

    this->timer.Tick();

//    this->renderTime.ElapsedRenderTime(elapsed);
//    this->renderTime.TotalRenderTime(this->timer.ElapsedTime());

    this->Update(this->renderTime);

    if (this->BeginDraw())
    {
        this->Draw(this->renderTime);
        this->EndDraw();
    }
}
