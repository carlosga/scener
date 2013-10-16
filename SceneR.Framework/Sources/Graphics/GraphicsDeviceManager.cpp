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

#include "Graphics/GraphicsDeviceManager.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/RendererWindow.hpp"

using namespace SceneR::Graphics;

GraphicsDeviceManager::GraphicsDeviceManager(Renderer& renderer)
    : renderer(renderer),
      graphicsDevice(GraphicsProfile::Core)
{
}

GraphicsDeviceManager::~GraphicsDeviceManager()
{
}

void GraphicsDeviceManager::ApplyChanges()
{
    this->graphicsDevice.ApplyChanges();
}

Boolean GraphicsDeviceManager::BeginDraw()
{
    // TODO: Implement
    return true;
}

void GraphicsDeviceManager::CreateDevice()
{
    // TODO: Implement
}

void GraphicsDeviceManager::EndDraw()
{
    // TODO: Implement
}

GraphicsDevice& GraphicsDeviceManager::GetGraphicsDevice()
{
    return this->graphicsDevice;
}

const Boolean GraphicsDeviceManager::GetAllowUserResizing() const
{
    return this->renderer.GetRendererWindow().GetAllowUserResizing();
}

void GraphicsDeviceManager::SetAllowUserResizing(const Boolean& allowUserResizing)
{
    this->renderer.GetRendererWindow().SetAllowUserResizing(allowUserResizing);
}

const std::wstring GraphicsDeviceManager::GetWindowTitle() const
{
    return this->renderer.GetRendererWindow().GetTitle();
}

void GraphicsDeviceManager::SetWindowTitle(const std::wstring& windowTitle)
{
    this->renderer.GetRendererWindow().SetTitle(windowTitle);
}

const Boolean GraphicsDeviceManager::GetFullScreen()
{
    return this->graphicsDevice.GetPresentationParameters().GetFullScreen();
}

void GraphicsDeviceManager::SetFullScreen(const Boolean& fullScreen)
{    
    this->graphicsDevice.GetPresentationParameters().SetFullScreen(fullScreen);
}

const Size GraphicsDeviceManager::GetPreferredBackBufferHeight()
{
    return this->graphicsDevice.GetPresentationParameters().GetBackBufferHeight();
}

void GraphicsDeviceManager::SetPreferredBackBufferHeight(const Size& preferredBackBufferHeight)
{
    this->graphicsDevice.GetPresentationParameters().SetBackBufferHeight(preferredBackBufferHeight);
}

const Size GraphicsDeviceManager::GetPreferredBackBufferWidth()
{
    return this->graphicsDevice.GetPresentationParameters().GetBackBufferWidth();
}

void GraphicsDeviceManager::SetPreferredBackBufferWidth(const Size& preferredBackBufferWidth)
{
    this->graphicsDevice.GetPresentationParameters().SetBackBufferWidth(preferredBackBufferWidth);
}
