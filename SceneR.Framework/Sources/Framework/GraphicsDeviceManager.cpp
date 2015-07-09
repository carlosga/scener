// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/GraphicsDeviceManager.hpp>

#include <Framework/PresentInterval.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/GraphicsAdapter.hpp>
#include <Framework/Renderer.hpp>

namespace SceneR
{
    namespace Framework
    {
        using SceneR::Graphics::GraphicsAdapter;
        using SceneR::Graphics::GraphicsDevice;

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

        GraphicsDeviceManager::~GraphicsDeviceManager()
        {
        }

        void GraphicsDeviceManager::Dispose()
        {
            if (this->graphicsDevice)
            {
                this->graphicsDevice->Dispose();
                this->graphicsDevice = nullptr;
            }
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

        bool GraphicsDeviceManager::BeginDraw()
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
                                                                  , Graphics::GraphicsProfile::HiDef);
        }

        GraphicsDevice& GraphicsDeviceManager::CurrentGraphicsDevice()
        {
            return *this->graphicsDevice;
        }

        const Graphics::GraphicsProfile& GraphicsDeviceManager::GraphicsProfile() const
        {
            return this->graphicsProfile;
        }

        void GraphicsDeviceManager::GraphicsProfile(const Graphics::GraphicsProfile& graphicsProfile)
        {
            this->graphicsProfile = graphicsProfile;
        }

        bool GraphicsDeviceManager::AllowUserResizing() const
        {
            return this->allowUserResizing;
        }

        void GraphicsDeviceManager::AllowUserResizing(const bool& allowUserResizing)
        {
            this->allowUserResizing = allowUserResizing;
        }

        const std::u16string& GraphicsDeviceManager::WindowTitle() const
        {
            return this->windowTitle;
        }

        void GraphicsDeviceManager::WindowTitle(const std::u16string& windowTitle)
        {
            this->windowTitle = windowTitle;
        }

        bool GraphicsDeviceManager::FullScreen() const
        {
            return this->fullScreen;
        }

        void GraphicsDeviceManager::FullScreen(const bool& fullScreen)
        {
            this->fullScreen = fullScreen;
        }

        std::uint32_t GraphicsDeviceManager::PreferredBackBufferHeight() const
        {
            return this->preferredBackBufferHeight;
        }

        void GraphicsDeviceManager::PreferredBackBufferHeight(const std::uint32_t& preferredBackBufferHeight)
        {
            this->preferredBackBufferHeight = preferredBackBufferHeight;
        }

        std::uint32_t GraphicsDeviceManager::PreferredBackBufferWidth() const
        {
            return this->preferredBackBufferWidth;
        }

        void GraphicsDeviceManager::PreferredBackBufferWidth(const std::uint32_t& preferredBackBufferWidth)
        {
            this->preferredBackBufferWidth = preferredBackBufferWidth;
        }
    }
}
