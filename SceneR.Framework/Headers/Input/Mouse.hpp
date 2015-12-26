// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef INPUT_MOUSE_HPP
#define INPUT_MOUSE_HPP

#include <cstdint>

#include <Input/Buttons.hpp>
#include <Input/ButtonState.hpp>

namespace System
{
    namespace Graphics
    {
        class DisplaySurface;
    }
}

namespace SceneR
{
    namespace Input
    {
        struct MouseState;

        // Allows retrieval of position and button clicks from a mouse input device.
        class Mouse
        {
        public:
            // Gets the current state of the mouse, including mouse position and buttons pressed.
            static MouseState get_state() noexcept;

            // Sets the position of the mouse cursor relative to the upper-left corner of the window.
            static void set_position(const std::uint32_t& x, const std::uint32_t& y) noexcept;

            // Gets or sets the window used for mouse processing.
            // Mouse coordinates returned by get_state are relative to the upper-left corner of this window.
            static void initialize(System::Graphics::DisplaySurface* surface) noexcept;

        private:
            static void cursor_position_callback(System::Graphics::DisplaySurface* surface
                                               , double                            xpos
                                               , double                            ypos) noexcept;

            static void mouse_button_callback(System::Graphics::DisplaySurface* surface
                                            , std::uint32_t                     button
                                            , std::uint32_t                     action
                                            , std::uint32_t                     mods) noexcept;

            static void scroll_wheel_callback(System::Graphics::DisplaySurface* surface
                                            , double                            xoffset
                                            , double                            yoffset) noexcept;

        private:
            Mouse() = delete;
            Mouse(const Mouse& mouse) = delete;
            Mouse& operator=(const Mouse& mouse) = delete;

        private:
            static System::Graphics::DisplaySurface* surface;
        };
    }
}

#endif  // INPUT_MOUSE_HPP
