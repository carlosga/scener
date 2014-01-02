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
#include <Graphics/GraphicsAdapter.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

GraphicsDeviceManager::GraphicsDeviceManager(Renderer& renderer)
    : renderer(renderer),
      graphicsDevice(nullptr),
      allowUserResizing(false),
      fullScreen(false),
      graphicsProfile(GraphicsProfile::Core),
      preferredBackBufferWidth(0),
      preferredBackBufferHeight(0),
      windowTitle(u"")
{
    this->renderer.Services().AddService<IGraphicsDeviceService>(*this);
}

GraphicsDeviceManager::~GraphicsDeviceManager()
{
}

void GraphicsDeviceManager::ApplyChanges()
{
    this->graphicsDevice->PresentationParameters().BackBufferWidth(this->preferredBackBufferWidth);
    this->graphicsDevice->PresentationParameters().BackBufferHeight(this->preferredBackBufferHeight);
    this->renderer.Window().Title(this->windowTitle);
    this->renderer.Window().AllowUserResizing(this->allowUserResizing);
    this->graphicsDevice->PresentationParameters().FullScreen(this->fullScreen);
    this->graphicsDevice->Viewport().Update(this->preferredBackBufferWidth, this->preferredBackBufferHeight);

    this->graphicsDevice->BlendState().Apply();
    this->graphicsDevice->RasterizerState().Apply();
    this->graphicsDevice->DepthStencilState().Apply();
}

Boolean GraphicsDeviceManager::BeginDraw()
{
    return true;
}

void GraphicsDeviceManager::EndDraw()
{
    this->graphicsDevice->Present();
}

void GraphicsDeviceManager::CreateDevice()
{
    this->graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsAdapter::DefaultAdapter(), GraphicsProfile::Core);
}

GraphicsDevice& GraphicsDeviceManager::CurrentGraphicsDevice()
{
    return *this->graphicsDevice;
}

const GraphicsProfile& GraphicsDeviceManager::GraphicsProfile() const
{
    return this->graphicsProfile;
}

void GraphicsDeviceManager::GraphicsProfile(const SceneR::Graphics::GraphicsProfile& graphicsProfile)
{
    this->graphicsProfile = graphicsProfile;
}

const Boolean& GraphicsDeviceManager::AllowUserResizing() const
{
    return this->allowUserResizing;
}

void GraphicsDeviceManager::AllowUserResizing(const Boolean& allowUserResizing)
{
    this->allowUserResizing = allowUserResizing;
}

const String& GraphicsDeviceManager::WindowTitle() const
{
    return this->windowTitle;
}

void GraphicsDeviceManager::WindowTitle(const String& windowTitle)
{
    this->windowTitle = windowTitle;
}

const Boolean& GraphicsDeviceManager::FullScreen() const
{
    return this->fullScreen;
}

void GraphicsDeviceManager::FullScreen(const Boolean& fullScreen)
{
    this->fullScreen = fullScreen;
}

const Size& GraphicsDeviceManager::PreferredBackBufferHeight() const
{
    return this->preferredBackBufferHeight;
}

void GraphicsDeviceManager::PreferredBackBufferHeight(const Size& preferredBackBufferHeight)
{
    this->preferredBackBufferHeight = preferredBackBufferHeight;
}

const Size& GraphicsDeviceManager::PreferredBackBufferWidth() const
{
    return this->preferredBackBufferWidth;
}

void GraphicsDeviceManager::PreferredBackBufferWidth(const Size& preferredBackBufferWidth)
{
    this->preferredBackBufferWidth = preferredBackBufferWidth;
}
