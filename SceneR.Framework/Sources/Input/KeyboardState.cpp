#include <Input/KeyboardState.hpp>
#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Input
    {
        // Initializes a new instance of the KeyboardState class.
        // Array or parameter list of Keys to initialize as pressed.
        //KeyboardState(Keys[] keys);

        KeyboardState::KeyboardState(GLFWwindow* windowHandle)
            : _windowHandle(windowHandle)
        {
        }

        KeyboardState::~KeyboardState()
        {
        }

        KeyState KeyboardState::GetKeyState(const Keys& key)
        {
            return KeyState::Down;
        }

        std::vector<Keys> KeyboardState::GetPressedKeys()
        {
            return { };
        }

        bool KeyboardState::IsKeyDown(const Keys& key)
        {
            return (glfwGetKey(_windowHandle, static_cast<int>(key)) == GLFW_PRESS);
        }

        bool KeyboardState::IsKeyUp(const Keys& key)
        {
            return (glfwGetKey(_windowHandle, static_cast<int>(key)) == GLFW_RELEASE);
        }
    }
}
