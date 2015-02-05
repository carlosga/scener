// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/Renderer.hpp>

#include <algorithm>
#include <thread>

#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

Renderer::Renderer(const String& rootDirectory)
    : components            ( 0 )
    , services              { }
    , graphicsDeviceManager { *this }
    , rendererWindow        { *this }
    , contentManager        { this->services, rootDirectory }
    , isFixedTimeStep       { true }
    , targetElapsedTime     { 10000000L / 60L }
    , timer                 { }
    , renderTime            { }
    , totalRenderTime       { TimeSpan::Zero }
    , isRunningSlowly       { false }
    , drawableComponents    ( 0 )
    , updateableComponents  ( 0 )
{
}

Renderer::~Renderer()
{
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
    this->PostProcessComponents();
    this->StartEventLoop();
    this->UnloadContent();
    this->EndRun();
}

void Renderer::Exit()
{
    this->graphicsDeviceManager.~GraphicsDeviceManager();
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
    for (auto& component : this->drawableComponents)
    {
        if (component->Visible())
        {
            component->Draw(renderTime);
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

void Renderer::Initialize()
{
    for (auto& component : this->components)
    {
        component->Initialize();
    }
}

const System::Boolean& Renderer::IsFixedTimeStep() const
{
    return this->isFixedTimeStep;
}

void Renderer::IsFixedTimeStep(const Boolean& isFixedTimeStep)
{
    this->isFixedTimeStep = isFixedTimeStep;
}

void Renderer::LoadContent()
{
}

const System::TimeSpan& Renderer::TargetElapsedTime() const
{
    return this->targetElapsedTime;
}

void Renderer::TargetElapsedTime(const TimeSpan& targetElapsedTime)
{
    this->targetElapsedTime = targetElapsedTime;
}

void Renderer::UnloadContent()
{
    this->drawableComponents.clear();
    this->updateableComponents.clear();
    this->components.clear();
}

void Renderer::Update(const RenderTime& renderTime)
{
    glfwPollEvents();

    for (auto& component : this->updateableComponents)
    {
        if (component->Enabled())
        {
            component->Update(renderTime);
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

/**
 * References:
 *      http://gafferongames.com/game-physics/fix-your-timestep/
 *      http://msdn.microsoft.com/en-us/library/bb203873.aspx
 */
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

void Renderer::PostProcessComponents()
{
    for (auto& component : this->components)
    {
        auto drawable = std::dynamic_pointer_cast<IDrawable>(component);

        if (drawable != nullptr)
        {
            this->drawableComponents.push_back(drawable);
        }

        auto updateable = std::dynamic_pointer_cast<IUpdateable>(component);

        if (updateable != nullptr)
        {
            this->updateableComponents.push_back(updateable);
        }
    }

    std::sort(this->drawableComponents.begin(), this->drawableComponents.end(),
              [](const std::shared_ptr<IDrawable>& a, const std::shared_ptr<IDrawable>& b) -> bool
              {
                  return (a->DrawOrder() < b->DrawOrder());
              });

    std::sort(this->updateableComponents.begin(), this->updateableComponents.end(),
              [](const std::shared_ptr<IUpdateable>& a, const std::shared_ptr<IUpdateable>& b) -> bool
              {
                  return (a->UpdateOrder() < b->UpdateOrder());
              });
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

        auto interval = this->targetElapsedTime - this->timer.ElapsedTimeStepTime();

        std::this_thread::sleep_for(interval.ToDuration<std::chrono::milliseconds>());
    }
}

void Renderer::VariableTimeStep()
{
}
