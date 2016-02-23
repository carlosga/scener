// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_KEYBOARD_HPP
#define SCENER_INPUT_KEYBOARD_HPP

#include <cstdint>
#include <vector>

#include "SceneR/Graphics/OpenGL/DisplaySurface.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL { class DisplaySurface; } } }

namespace SceneR { namespace Input {

enum class Keys     : std::uint32_t;
enum class KeyState : std::uint32_t;

class KeyboardState;

/// Allows retrieval of keystrokes from a keyboard input device.
class Keyboard
{
public:
    /// Returns the current keyboard state.
    /// \returns current keyboard state.
    static KeyboardState get_state() noexcept;

    /// Gets or sets the window used for mouse processing.
    static void initialize(Graphics::OpenGL::DisplaySurface* s) noexcept;

private:
    static void key_callback(Graphics::OpenGL::DisplaySurface* s, int key, int scancode, int action, int mods) noexcept;

private:
    Keyboard() = delete;
    Keyboard(const Keyboard& keyboard) = delete;
    Keyboard& operator=(const Keyboard& keyboard) = delete;

private:
    static Graphics::OpenGL::DisplaySurface* surface;
};

}}

#endif // SCENER_INPUT_KEYBOARD_HPP
