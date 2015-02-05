// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/GraphicsDeviceManager.hpp>

#include <Framework/PresentInterval.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/GraphicsAdapter.hpp>
#include <Framework/Renderer.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

GraphicsDeviceManager::GraphicsDeviceManager(Renderer& renderer)
    : renderer                  ( renderer )
    , graphicsDevice            { nullptr }
    , allowUserResizing         { false }
    , fullScreen                { false }
    , graphicsProfile           { SceneR::Graphics::GraphicsProfile::HiDef }
    , preferredBackBufferWidth  { 0 }
    , preferredBackBufferHeight { 0 }
    , windowTitle               { u"" }
{
    this->renderer.Services().AddService<IGraphicsDeviceService>(*this);
}

void GraphicsDeviceManager::ApplyChanges()
{
    this->graphicsDevice->PresentationParameters().BackBufferWidth(this->preferredBackBufferWidth);
    this->graphicsDevice->PresentationParameters().BackBufferHeight(this->preferredBackBufferHeight);
    this->graphicsDevice->PresentationParameters().FullScreen(this->fullScreen);
    this->renderer.Window().Title(this->windowTitle);
    this->renderer.Window().AllowUserResizing(this->allowUserResizing);
    this->graphicsDevice->Viewport().Update(this->preferredBackBufferWidth, this->preferredBackBufferHeight);

    this->graphicsDevice->BlendState().Apply();
    this->graphicsDevice->RasterizerState().Apply();
    this->graphicsDevice->DepthStencilState().Apply();

    switch (this->graphicsDevice->PresentationParameters().PresentInterval())
    {
        case PresentInterval::Default:
        case PresentInterval::One:
            glfwSwapInterval(1);
            break;

        case PresentInterval::Two:
            glfwSwapInterval(2);
            break;

        case PresentInterval::Immediate:
            glfwSwapInterval(0);
    }
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
    if (!glfwInit())
    {
        throw std::runtime_error("glfwInit failed");
    }

    this->graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsAdapter::DefaultAdapter()
                                                          , SceneR::Graphics::GraphicsProfile::HiDef);
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
