// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_KEYS_HPP
#define SCENER_INPUT_KEYS_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Input {

enum class Keys : std::uint32_t
{
    /**
     * Reserved.
     */
    none = 0,
    /**
     * BACKSPACE key.
     */
    Back = 1,
    /**
     * TAB key.
     */
    Tab = 2,
    /**
     * ENTER key.
     */
    Enter = 3,
    /**
     * CAPS LOCK key.
     */
    CapsLock = 4,
    /**
     * ESC key.
     */
    Escape = 5,
    /**
     * SPACEBAR key.
     */
    Space = 6,
    /**
     * PAGE UP key.
     */
    PageUp = 7,
    /**
     * PAGE DOWN key.
     */
    PageDown = 8,
    /**
     * END key.
     */
    End = 9,
    /**
     * HOME key.
     */
    Home = 10,
    /**
     * LEFT ARROW key.
     */
    Left = 11,
    /**
     * UP ARROW key.
     */
    Up = 12,
    /**
     * RIGHT ARROW key.
     */
    Right = 13,
    /**
     * DOWN ARROW key.
     */
    Down = 14,
    /**
     * PRINT SCREEN key.
     */
    PrintScreen = 15,
    /**
     * INS key.
     */
    Insert = 16,
    /**
     * DEL key.
     */
    Delete = 17,
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
    NumPad0 = 18,
    /**
     * Numeric keypad 1 key.
     */
    NumPad1 = 19,
    /**
     * Numeric keypad 2 key.
     */
    NumPad2 = 20,
    /**
     * Numeric keypad 3 key.
     */
    NumPad3 = 21,
    /**
     * Numeric keypad 4 key.
     */
    NumPad4 = 22,
    /**
     * Numeric keypad 5 key.
     */
    NumPad5 = 23,
    /**
     * Numeric keypad 6 key.
     */
    NumPad6 = 24,
    /**
     * Numeric keypad 7 key.
     */
    NumPad7 = 25,
    /**
     * Numeric keypad 8 key.
     */
    NumPad8 = 26,
    /**
     * Numeric keypad 9 key.
     */
    NumPad9 = 27,
    /**
     * Multiply key.
     */
    Multiply = 28,
    /**
     * Add key.
     */
    Add = 29,
    /**
     * Subtract key.
     */
    Subtract = 30,
    /**
     * Decimal key.
     */
    Decimal = 31,
    /**
     * Divide key.
     */
    Divide = 32,
    /**
     * F1 key.
     */
    F1 = 33,
    /**
     * F2 key.
     */
    F2 = 34,
    /**
     * F3 key.
     */
    F3 = 35,
    /**
     * F4 key.
     */
    F4 = 36,
    /**
     * F5 key.
     */
    F5 = 37,
    /**
     * F6 key.
     */
    F6 = 38,
    /**
     * F7 key.
     */
    F7 = 39,
    /**
     * F8 key.
     */
    F8 = 40,
    /**
     * F9 key.
     */
    F9 = 41,
    /**
     * F10 key.
     */
    F10 = 42,
    /**
     * F11 key.
     */
    F11 = 43,
    /**
     * F12 key.
     */
    F12 = 44,
    /**
     * F13 key.
     */
    F13 = 45,
    /**
     * F14 key.
     */
    F14 = 46,
    /**
     * F15 key.
     */
    F15 = 47,
    /**
     * F16 key.
     */
    F16 = 48,
    /**
     * F17 key.
     */
    F17 = 49,
    /**
     * F18 key.
     */
    F18 = 50,
    /**
     * F19 key.
     */
    F19 = 51,
    /**
     * F20 key.
     */
    F20 = 52,
    /**
     * F21 key.
     */
    F21 = 53,
    /**
     * F22 key.
     */
    F22 = 54,
    /**
     * F23 key.
     */
    F23 = 55,
    /**
     * F24 key.
     */
    F24 = 56,
    /**
     * NUM LOCK key.
     */
    NumLock = 57,
    /**
     * SCROLL LOCK key.
     */
    Scroll = 58,
    /**
     * Left SHIFT key.
     */
    LeftShift = 59,
    /**
     * Right SHIFT key.
     */
    RightShift = 60,
    /**
     * Left CONTROL key.
     */
    LeftControl = 61,
    /**
     * Right CONTROL key.
     */
    RightControl = 62,
    /**
     * Left ALT key.
     */
    LeftAlt = 63,
    /**
     * Right ALT key.
     */
    RightAlt = 64,
    /**
     * The OEM Semicolon key on a US standard keyboard.
     */
    OemSemicolon = 91,
    /**
     * For any country/region, the '.' key.
     */
    OemPeriod = 92,
    /**
     * The OEM angle bracket or backslash key on the RT 102 key keyboard.
     */
    OemBackslash = 93,
    /**
     * PAUSE key.
     */
    Pause = 94
};

}}

#endif // SCENER_INPUT_KEYS_HPP
