// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/RendererWindow.hpp"

#include <cstddef>
#include <iostream>

#include "SceneR/Graphics/OpenGL/Platform.hpp"
#include "SceneR/Graphics/OpenGL/DisplayDevice.hpp"
#include "SceneR/Graphics/OpenGL/DisplaySurface.hpp"
#include "SceneR/Graphics/GraphicsDeviceManager.hpp"
#include "SceneR/Graphics/Renderer.hpp"
#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Input/Keyboard.hpp"
#include "SceneR/Input/KeyboardState.hpp"
#include "SceneR/Input/Keys.hpp"
#include "SceneR/Input/Mouse.hpp"

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Graphics::DisplayDevice;
        using SceneR::Graphics::DisplaySurface;
        using SceneR::Input::Keyboard;
        using SceneR::Input::KeyboardState;
        using SceneR::Input::Keys;
        using SceneR::Input::Mouse;

        RendererWindow::RendererWindow(gsl::not_null<Renderer*> renderer)
            : _renderer { renderer }
        {
        }

        RendererWindow::~RendererWindow()
        {
            close();
        }

        const std::string& RendererWindow::title() const noexcept
        {
            return _title;
        }

        void RendererWindow::title(const std::string& title) noexcept
        {
            _title = title;
            // TODO
            // Set window title
        }

        bool RendererWindow::allow_user_resizing() const noexcept
        {
            return _renderer->_graphics_device_manager->allow_user_resizing;
        }

        void RendererWindow::allow_user_resizing(const bool& allowUserResizing) noexcept
        {
            _renderer->_graphics_device_manager->allow_user_resizing = allowUserResizing;
        }

        DisplayDevice* RendererWindow::display_device() const noexcept
        {
            return _displayDevice.get();
        }

        DisplaySurface* RendererWindow::display_surface() const noexcept
        {
            return _displaySurface.get();
        }

        void RendererWindow::open()
        {
            auto width  = _renderer->_graphics_device_manager->preferred_back_buffer_width;
            auto height = _renderer->_graphics_device_manager->preferred_back_buffer_height;

            _displayDevice  = std::make_unique<DisplayDevice>();
            _displaySurface = std::make_unique<DisplaySurface>(_displayDevice.get());

            if (!_displayDevice->open())
            {
                throw std::runtime_error("An error has occurred while opening the display device.");
            }

            if (!_displaySurface->create(width, height))
            {
                throw std::runtime_error("An error has occurred while creatring the display surface.");
            }

            // initialize input
            initialize_input();
        }

        void RendererWindow::show() const noexcept
        {
            _displaySurface->clear();
            _displaySurface->show();
        }

        void RendererWindow::close() noexcept
        {
            if (_displaySurface.get())
            {
                _displaySurface->destroy();
                _displaySurface = nullptr;
            }
            if (_displayDevice.get())
            {
                _displayDevice->destroy();
                _displayDevice = nullptr;
            }
        }

        void RendererWindow::initialize_input() const noexcept
        {
            // initialize keyboard input
            Keyboard::initialize(_displaySurface.get());

            // initialize mouse input
            Mouse::initialize(_displaySurface.get());
        }

        bool RendererWindow::should_close() const noexcept
        {
            auto fullScreen    = _renderer->_graphics_device_manager->full_screen;
            auto shouldClose   = _displaySurface->should_close();
            auto keyboardState = Keyboard::get_state();
            auto isEscPressed  = keyboardState.is_key_down(Keys::Escape);

            return ((!fullScreen && isEscPressed) || shouldClose);
        }

        void RendererWindow::pool_events() const noexcept
        {
            _displaySurface->pool_events();
        }
    }
}
