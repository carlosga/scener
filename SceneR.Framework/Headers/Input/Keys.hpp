// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef KEYS_HPP
#define KEYS_HPP

#include <cstdint>
#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Input
    {
        enum class Keys : std::uint32_t
        {
            /**
             * Reserved.
             */
            None = 0,
            /**
             * BACKSPACE key.
             */
            Back = GLFW_KEY_BACKSPACE,
            /**
             * TAB key.
             */
            Tab = GLFW_KEY_TAB,
            /**
             * ENTER key.
             */
            Enter = GLFW_KEY_ENTER,
            /**
             * CAPS LOCK key.
             */
            CapsLock = GLFW_KEY_CAPS_LOCK,
            /**
             * ESC key.
             */
            Escape = GLFW_KEY_ESCAPE,
            /**
             * SPACEBAR key.
             */
            Space = GLFW_KEY_SPACE,
            /**
             * PAGE UP key.
             */
            PageUp = GLFW_KEY_PAGE_UP,
            /**
             * PAGE DOWN key.
             */
            PageDown = GLFW_KEY_PAGE_DOWN,
            /**
             * END key.
             */
            End = GLFW_KEY_END,
            /**
             * HOME key.
             */
            Home = GLFW_KEY_HOME,
            /**
             * LEFT ARROW key.
             */
            Left = GLFW_KEY_LEFT,
            /**
             * UP ARROW key.
             */
            Up = GLFW_KEY_UP,
            /**
             * RIGHT ARROW key.
             */
            Right = GLFW_KEY_RIGHT,
            /**
             * DOWN ARROW key.
             */
            Down = GLFW_KEY_DOWN,
            /**
             * PRINT SCREEN key.
             */
            PrintScreen = GLFW_KEY_PRINT_SCREEN,
            /**
             * INS key.
             */
            Insert = GLFW_KEY_INSERT,
            /**
             * DEL key.
             */
            Delete = GLFW_KEY_DELETE,
            /**
             * A key.
             */
            A = 65,
            /**
             * B key.
             */
            B = 66,
            /**
             * C key.
             */
            C = 67,
            /**
             * D key.
             */
            D = 68,
            /**
             * E key.
             */
            E = 69,
            /**
             * F key.
             */
            F = 70,
            /**
             * G key.
             */
            G = 71,
            /**
             * H key.
             */
            H = 72,
            /**
             * I key.
             */
            I = 73,
            /**
             * J key.
             */
            J = 74,
            /**
             * K key.
             */
            K = 75,
            /**
             * L key.
             */
            L = 76,
            /**
             * M key.
             */
            M = 77,
            /**
             * N key.
             */
            N = 78,
            /**
             * O key.
             */
            O = 79,
            /**
             * P key.
             */
            P = 80,
            /**
             * Q key.
             */
            Q = 81,
            /**
             * R key.
             */
            R = 82,
            /**
             * S key.
             */
            S = 83,
            /**
             * T key.
             */
            T = 84,
            /**
             * U key.
             */
            U = 85,
            /**
             * V key.
             */
            V = 86,
            /**
             * W key.
             */
            W = 87,
            /**
             * X key.
             */
            X = 88,
            /**
             * Y key.
             */
            Y = 89,
            /**
             * Z key.
             */
            Z = 90,
            /**
             * Numeric keypad 0 key.
             */
            NumPad0 = GLFW_KEY_KP_0,
            /**
             * Numeric keypad 1 key.
             */
            NumPad1 = GLFW_KEY_KP_1,
            /**
             * Numeric keypad 2 key.
             */
            NumPad2 = GLFW_KEY_KP_2,
            /**
             * Numeric keypad 3 key.
             */
            NumPad3 = GLFW_KEY_KP_3,
            /**
             * Numeric keypad 4 key.
             */
            NumPad4 = GLFW_KEY_KP_4,
            /**
             * Numeric keypad 5 key.
             */
            NumPad5 = GLFW_KEY_KP_5,
            /**
             * Numeric keypad 6 key.
             */
            NumPad6 = GLFW_KEY_KP_6,
            /**
             * Numeric keypad 7 key.
             */
            NumPad7 = GLFW_KEY_KP_7,
            /**
             * Numeric keypad 8 key.
             */
            NumPad8 = GLFW_KEY_KP_8,
            /**
             * Numeric keypad 9 key.
             */
            NumPad9 = GLFW_KEY_KP_9,
            /**
             * Multiply key.
             */
            Multiply = GLFW_KEY_KP_MULTIPLY,
            /**
             * Add key.
             */
            Add = GLFW_KEY_KP_ADD,
            /**
             * Separator key.
             */
            // Separator = 108,
            /**
             * Subtract key.
             */
            Subtract = GLFW_KEY_KP_SUBTRACT,
            /**
             * Decimal key.
             */
            Decimal = GLFW_KEY_KP_DECIMAL,
            /**
             * Divide key.
             */
            Divide = GLFW_KEY_KP_DIVIDE,
            /**
             * F1 key.
             */
            F1 = GLFW_KEY_F1,
            /**
             * F2 key.
             */
            F2 = GLFW_KEY_F2,
            /**
             * F3 key.
             */
            F3 = GLFW_KEY_F3,
            /**
             * F4 key.
             */
            F4 = GLFW_KEY_F4,
            /**
             * F5 key.
             */
            F5 = GLFW_KEY_F5,
            /**
             * F6 key.
             */
            F6 = GLFW_KEY_F6,
            /**
             * F7 key.
             */
            F7 = GLFW_KEY_F7,
            /**
             * F8 key.
             */
            F8 = GLFW_KEY_F8,
            /**
             * F9 key.
             */
            F9 = GLFW_KEY_F9,
            /**
             * F10 key.
             */
            F10 = GLFW_KEY_F10,
            /**
             * F11 key.
             */
            F11 = GLFW_KEY_F11,
            /**
             * F12 key.
             */
            F12 = GLFW_KEY_F12,
            /**
             * F13 key.
             */
            F13 = GLFW_KEY_F13,
            /**
             * F14 key.
             */
            F14 = GLFW_KEY_F14,
            /**
             * F15 key.
             */
            F15 = GLFW_KEY_F15,
            /**
             * F16 key.
             */
            F16 = GLFW_KEY_F16,
            /**
             * F17 key.
             */
            F17 = GLFW_KEY_F17,
            /**
             * F18 key.
             */
            F18 = GLFW_KEY_F18,
            /**
             * F19 key.
             */
            F19 = GLFW_KEY_F19,
            /**
             * F20 key.
             */
            F20 = GLFW_KEY_F20,
            /**
             * F21 key.
             */
            F21 = GLFW_KEY_F21,
            /**
             * F22 key.
             */
            F22 = GLFW_KEY_F22,
            /**
             * F23 key.
             */
            F23 = GLFW_KEY_F23,
            /**
             * F24 key.
             */
            F24 = GLFW_KEY_F24,
            /**
             * NUM LOCK key.
             */
            NumLock = GLFW_KEY_NUM_LOCK,
            /**
             * SCROLL LOCK key.
             */
            Scroll = GLFW_KEY_SCROLL_LOCK,
            /**
             * Left SHIFT key.
             */
            LeftShift = GLFW_KEY_LEFT_SHIFT,
            /**
             * Right SHIFT key.
             */
            RightShift = GLFW_KEY_RIGHT_SHIFT,
            /**
             * Left CONTROL key.
             */
            LeftControl = GLFW_KEY_LEFT_CONTROL,
            /**
             * Right CONTROL key.
             */
            RightControl = GLFW_KEY_RIGHT_CONTROL,
            /**
             * Left ALT key.
             */
            LeftAlt = GLFW_KEY_LEFT_ALT,
            /**
             * Right ALT key.
             */
            RightAlt = GLFW_KEY_RIGHT_ALT,
            /**
             * The OEM Semicolon key on a US standard keyboard.
             */
            OemSemicolon = GLFW_KEY_SEMICOLON,
            /**
             * For any country/region, the '.' key.
             */
            OemPeriod = GLFW_KEY_PERIOD,
            /**
             * The OEM angle bracket or backslash key on the RT 102 key keyboard.
             */
            OemBackslash = GLFW_KEY_BACKSLASH,
            /**
             * PAUSE key.
             */
            Pause = GLFW_KEY_PAUSE,
        };
    }
}

#endif // KEYS_HPP
