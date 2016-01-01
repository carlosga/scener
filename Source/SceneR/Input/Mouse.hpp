// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_MOUSE_HPP
#define SCENER_INPUT_MOUSE_HPP

#include <cstdint>

namespace SceneR { namespace Graphics { namespace OpenGL { class DisplaySurface; } } }

namespace SceneR { namespace Input {

enum class Buttons     : std::uint32_t;
enum class ButtonState : std::uint32_t;

struct MouseState;

// Allows retrieval of position and button clicks from a mouse input device.
class Mouse
{
public:
    // Gets the current state of the mouse, including mouse position and buttons pressed.
    static MouseState get_state() noexcept;

    // Sets the position of the mouse cursor relative to the upper-left corner of the window.
    static void set_position(std::uint32_t x, std::uint32_t y) noexcept;

    // Gets or sets the window used for mouse processing.
    // Mouse coordinates returned by get_state are relative to the upper-left corner of this window.
    static void initialize(SceneR::Graphics::OpenGL::DisplaySurface* surface) noexcept;

private:
    static void cursor_position_callback(SceneR::Graphics::OpenGL::DisplaySurface* surface
                                       , double                                    xpos
                                       , double                                    ypos) noexcept;

    static void mouse_button_callback(SceneR::Graphics::OpenGL::DisplaySurface* surface
                                    , std::uint32_t                             button
                                    , std::uint32_t                             action
                                    , std::uint32_t                             mods) noexcept;

    static void scroll_wheel_callback(SceneR::Graphics::OpenGL::DisplaySurface* surface
                                    , double                                    xoffset
                                    , double                                    yoffset) noexcept;

private:
    Mouse() = delete;
    Mouse(const Mouse& mouse) = delete;
    Mouse& operator=(const Mouse& mouse) = delete;

private:
    static SceneR::Graphics::OpenGL::DisplaySurface* surface;
};

}}

#endif // SCENER_INPUT_MOUSE_HPP
