#include <Input/Keyboard.hpp>

#include <System/Graphics/Platform.hpp>
#include <Input/KeyboardState.hpp>

namespace SceneR
{
    namespace Input
    {
        // Returns the current keyboard state.
        KeyboardState Keyboard::GetState()
        {
            return KeyboardState(Keyboard::WindowHandle);
        }

        // Gets or sets the window used for mouse processing.
        void Keyboard::Initialize(GLFWwindow* window)
        {
            WindowHandle = window;

            // Enable sticky keys
            glfwSetInputMode(WindowHandle, GLFW_STICKY_KEYS, 1);

            // Initialize key callback
            // glfwSetKeyCallback(WindowHandle, Keyboard::KeyCallback);
        }

        void Keyboard::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_E && action == GLFW_PRESS)
            {
                int a = 1;
            }

//            if (key == GLFW_KEY_E && action == GLFW_PRESS)
//                activate_airship();
        }

        GLFWwindow* Keyboard::WindowHandle;
    }
}
