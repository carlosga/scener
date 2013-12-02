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
#include <chrono>
#include <thread>

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
      isFixedTimeStep(true),
      targetElapsedTime(1000.0 / 60.0),
      timer(),
      renderTime(),
      totalRenderTime(),
      isRunningSlowly(false)
{
}

Renderer::~Renderer()
{
    this->Finalize();
    this->Exit();
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

std::vector<std::shared_ptr<IComponent>>& Renderer::Components()
{
    return this->components;
}

RendererServiceContainer& Renderer::Services()
{
    return this->services;
}

void Renderer::Run()
{
    this->BeginRun();
    this->CreateDevice();
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

const System::Boolean& Renderer::IsFixedTimeStep() const
{
    return this->isFixedTimeStep;
}

void Renderer::IsFixedTimeStep(const System::Boolean& isFixedTimeStep)
{
    this->isFixedTimeStep = isFixedTimeStep;
}

void Renderer::LoadContent()
{
}

const System::MilliSeconds& Renderer::TargetElapsedTime() const
{
    return this->targetElapsedTime;
}

void Renderer::TargetElapsedTime(const System::MilliSeconds& targetElapsedTime)
{
    this->targetElapsedTime = targetElapsedTime;
}

void Renderer::UnloadContent()
{
}

void Renderer::Update(const RenderTime& renderTime)
{
    glfwPollEvents();

    for (auto& component : this->components)
    {
        auto updateable = std::dynamic_pointer_cast<IUpdateable>(component);

        if (updateable != nullptr && updateable->Enabled())
        {
            updateable->Update(renderTime);
        }
    }
}

void Renderer::StartEventLoop()
{
    this->timer.Reset();

    do
    {

        this->TimeStep();

    } while (!this->rendererWindow.ShouldClose());
}

void Renderer::TimeStep()
{
    if (this->IsFixedTimeStep())
    {
        this->FixedTimeStep();
    }
    else
    {
        this->VariableTimeStep();
    }
}

void Renderer::CreateDevice()
{
    this->graphicsDeviceManager.CreateDevice();
    this->rendererWindow.Open();
    this->graphicsDeviceManager.ApplyChanges();
}

void Renderer::FixedTimeStep()
{
    this->renderTime.ElapsedRenderTime(this->timer.ElapsedTimeStepTime());
    this->renderTime.TotalRenderTime(this->timer.ElapsedTime());
    this->renderTime.IsRunningSlowly(this->isRunningSlowly);

    this->timer.UpdateTimeStep();

    this->Update(this->renderTime);

    this->isRunningSlowly = (this->timer.ElapsedTimeStepTime() > this->targetElapsedTime);

    if (!this->isRunningSlowly)
    {
        if (this->BeginDraw())
        {
            this->Draw(this->renderTime);
            this->EndDraw();
        }

        std::this_thread::sleep_for(this->targetElapsedTime - this->timer.ElapsedTimeStepTime());
    }
}

void Renderer::VariableTimeStep()
{
    glfwWaitEvents();
}
