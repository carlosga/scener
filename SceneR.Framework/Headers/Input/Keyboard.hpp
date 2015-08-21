#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cstdint>
#include <vector>

#include <Input/Keys.hpp>
#include <Input/KeyState.hpp>

struct GLFWwindow;

namespace SceneR
{
    namespace Input
    {
        struct KeyboardState;

        // Allows retrieval of keystrokes from a keyboard input device.
        class Keyboard
        {
        public:
            // Returns the current keyboard state.
            static KeyboardState GetState();

            // Gets or sets the window used for mouse processing.
            static void Initialize(GLFWwindow* window);

        private:
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

            static GLFWwindow* WindowHandle;

        private:
            Keyboard() = delete;
            Keyboard(const Keyboard& keyboard) = delete;
            Keyboard& operator=(const Keyboard& keyboard) = delete;
        };
    }
}

#endif // KEYBOARD_HPP
