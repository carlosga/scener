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
            /// <summary>
            /// Reserved.
            /// </summary>
            None = 0,
            /// <summary>
            /// BACKSPACE key.
            /// </summary>
            Back = GLFW_KEY_BACKSPACE,
            /// <summary>
            /// TAB key.
            /// </summary>
            Tab = GLFW_KEY_TAB,
            /// <summary>
            /// ENTER key.
            /// </summary>
            Enter = GLFW_KEY_ENTER,
            /// <summary>
            /// CAPS LOCK key.
            /// </summary>
            CapsLock = GLFW_KEY_CAPS_LOCK,
            /// <summary>
            /// ESC key.
            /// </summary>
            Escape = GLFW_KEY_ESCAPE,
            /// <summary>
            /// SPACEBAR key.
            /// </summary>
            Space = GLFW_KEY_SPACE,
            /// <summary>
            /// PAGE UP key.
            /// </summary>
            PageUp = GLFW_KEY_PAGE_UP,
            /// <summary>
            /// PAGE DOWN key.
            /// </summary>
            PageDown = GLFW_KEY_PAGE_DOWN,
            /// <summary>
            /// END key.
            /// </summary>
            End = GLFW_KEY_END,
            /// <summary>
            /// HOME key.
            /// </summary>
            Home = GLFW_KEY_HOME,
            /// <summary>
            /// LEFT ARROW key.
            /// </summary>
            Left = GLFW_KEY_LEFT,
            /// <summary>
            /// UP ARROW key.
            /// </summary>
            Up = GLFW_KEY_UP,
            /// <summary>
            /// RIGHT ARROW key.
            /// </summary>
            Right = GLFW_KEY_RIGHT,
            /// <summary>
            /// DOWN ARROW key.
            /// </summary>
            Down = GLFW_KEY_DOWN,
            /// <summary>
            /// SELECT key.
            /// </summary>
            // Select = 41,
            /// <summary>
            /// PRINT key.
            /// </summary>
            // Print = 42,
            /// <summary>
            /// EXECUTE key.
            /// </summary>
            // Execute = 43,
            /// <summary>
            /// PRINT SCREEN key.
            /// </summary>
            PrintScreen = GLFW_KEY_PRINT_SCREEN,
            /// <summary>
            /// INS key.
            /// </summary>
            Insert = GLFW_KEY_INSERT,
            /// <summary>
            /// DEL key.
            /// </summary>
            Delete = GLFW_KEY_DELETE,
            /// <summary>
            /// HELP key.
            /// </summary>
            // Help = 47,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // D0 = 48,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // D1 = 49,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // D2 = 50,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // D3 = 51,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // D4 = 52,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // D5 = 53,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // D6 = 54,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // D7 = 55,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // D8 = 56,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // D9 = 57,
            /// <summary>
            /// A key.
            /// </summary>
            A = 65,
            /// <summary>
            /// B key.
            /// </summary>
            B = 66,
            /// <summary>
            /// C key.
            /// </summary>
            C = 67,
            /// <summary>
            /// D key.
            /// </summary>
            D = 68,
            /// <summary>
            /// E key.
            /// </summary>
            E = 69,
            /// <summary>
            /// F key.
            /// </summary>
            F = 70,
            /// <summary>
            /// G key.
            /// </summary>
            G = 71,
            /// <summary>
            /// H key.
            /// </summary>
            H = 72,
            /// <summary>
            /// I key.
            /// </summary>
            I = 73,
            /// <summary>
            /// J key.
            /// </summary>
            J = 74,
            /// <summary>
            /// K key.
            /// </summary>
            K = 75,
            /// <summary>
            /// L key.
            /// </summary>
            L = 76,
            /// <summary>
            /// M key.
            /// </summary>
            M = 77,
            /// <summary>
            /// N key.
            /// </summary>
            N = 78,
            /// <summary>
            /// O key.
            /// </summary>
            O = 79,
            /// <summary>
            /// P key.
            /// </summary>
            P = 80,
            /// <summary>
            /// Q key.
            /// </summary>
            Q = 81,
            /// <summary>
            /// R key.
            /// </summary>
            R = 82,
            /// <summary>
            /// S key.
            /// </summary>
            S = 83,
            /// <summary>
            /// T key.
            /// </summary>
            T = 84,
            /// <summary>
            /// U key.
            /// </summary>
            U = 85,
            /// <summary>
            /// V key.
            /// </summary>
            V = 86,
            /// <summary>
            /// W key.
            /// </summary>
            W = 87,
            /// <summary>
            /// X key.
            /// </summary>
            X = 88,
            /// <summary>
            /// Y key.
            /// </summary>
            Y = 89,
            /// <summary>
            /// Z key.
            /// </summary>
            Z = 90,
            /// <summary>
            /// Left Windows key.
            /// </summary>
            // LeftWindows = 91,
            /// <summary>
            /// Right Windows key.
            /// </summary>
            // RightWindows = 92,
            /// <summary>
            /// Applications key.
            /// </summary>
            // Apps = 93,
            /// <summary>
            /// Computer Sleep key.
            /// </summary>
            // Sleep = 95,
            /// <summary>
            /// Numeric keypad 0 key.
            /// </summary>
            NumPad0 = GLFW_KEY_KP_0,
            /// <summary>
            /// Numeric keypad 1 key.
            /// </summary>
            NumPad1 = GLFW_KEY_KP_1,
            /// <summary>
            /// Numeric keypad 2 key.
            /// </summary>
            NumPad2 = GLFW_KEY_KP_2,
            /// <summary>
            /// Numeric keypad 3 key.
            /// </summary>
            NumPad3 = GLFW_KEY_KP_3,
            /// <summary>
            /// Numeric keypad 4 key.
            /// </summary>
            NumPad4 = GLFW_KEY_KP_4,
            /// <summary>
            /// Numeric keypad 5 key.
            /// </summary>
            NumPad5 = GLFW_KEY_KP_5,
            /// <summary>
            /// Numeric keypad 6 key.
            /// </summary>
            NumPad6 = GLFW_KEY_KP_6,
            /// <summary>
            /// Numeric keypad 7 key.
            /// </summary>
            NumPad7 = GLFW_KEY_KP_7,
            /// <summary>
            /// Numeric keypad 8 key.
            /// </summary>
            NumPad8 = GLFW_KEY_KP_8,
            /// <summary>
            /// Numeric keypad 9 key.
            /// </summary>
            NumPad9 = GLFW_KEY_KP_9,
            /// <summary>
            /// Multiply key.
            /// </summary>
            Multiply = GLFW_KEY_KP_MULTIPLY,
            /// <summary>
            /// Add key.
            /// </summary>
            Add = GLFW_KEY_KP_ADD,
            /// <summary>
            /// Separator key.
            /// </summary>
            // Separator = 108,
            /// <summary>
            /// Subtract key.
            /// </summary>
            Subtract = GLFW_KEY_KP_SUBTRACT,
            /// <summary>
            /// Decimal key.
            /// </summary>
            Decimal = GLFW_KEY_KP_DECIMAL,
            /// <summary>
            /// Divide key.
            /// </summary>
            Divide = GLFW_KEY_KP_DIVIDE,
            /// <summary>
            /// F1 key.
            /// </summary>
            F1 = GLFW_KEY_F1,
            /// <summary>
            /// F2 key.
            /// </summary>
            F2 = GLFW_KEY_F2,
            /// <summary>
            /// F3 key.
            /// </summary>
            F3 = GLFW_KEY_F3,
            /// <summary>
            /// F4 key.
            /// </summary>
            F4 = GLFW_KEY_F4,
            /// <summary>
            /// F5 key.
            /// </summary>
            F5 = GLFW_KEY_F5,
            /// <summary>
            /// F6 key.
            /// </summary>
            F6 = GLFW_KEY_F6,
            /// <summary>
            /// F7 key.
            /// </summary>
            F7 = GLFW_KEY_F7,
            /// <summary>
            /// F8 key.
            /// </summary>
            F8 = GLFW_KEY_F8,
            /// <summary>
            /// F9 key.
            /// </summary>
            F9 = GLFW_KEY_F9,
            /// <summary>
            /// F10 key.
            /// </summary>
            F10 = GLFW_KEY_F10,
            /// <summary>
            /// F11 key.
            /// </summary>
            F11 = GLFW_KEY_F11,
            /// <summary>
            /// F12 key.
            /// </summary>
            F12 = GLFW_KEY_F12,
            /// <summary>
            /// F13 key.
            /// </summary>
            F13 = GLFW_KEY_F13,
            /// <summary>
            /// F14 key.
            /// </summary>
            F14 = GLFW_KEY_F14,
            /// <summary>
            /// F15 key.
            /// </summary>
            F15 = GLFW_KEY_F15,
            /// <summary>
            /// F16 key.
            /// </summary>
            F16 = GLFW_KEY_F16,
            /// <summary>
            /// F17 key.
            /// </summary>
            F17 = GLFW_KEY_F17,
            /// <summary>
            /// F18 key.
            /// </summary>
            F18 = GLFW_KEY_F18,
            /// <summary>
            /// F19 key.
            /// </summary>
            F19 = GLFW_KEY_F19,
            /// <summary>
            /// F20 key.
            /// </summary>
            F20 = GLFW_KEY_F20,
            /// <summary>
            /// F21 key.
            /// </summary>
            F21 = GLFW_KEY_F21,
            /// <summary>
            /// F22 key.
            /// </summary>
            F22 = GLFW_KEY_F22,
            /// <summary>
            /// F23 key.
            /// </summary>
            F23 = GLFW_KEY_F23,
            /// <summary>
            /// F24 key.
            /// </summary>
            F24 = GLFW_KEY_F24,
            /// <summary>
            /// NUM LOCK key.
            /// </summary>
            NumLock = GLFW_KEY_NUM_LOCK,
            /// <summary>
            /// SCROLL LOCK key.
            /// </summary>
            Scroll = GLFW_KEY_SCROLL_LOCK,
            /// <summary>
            /// Left SHIFT key.
            /// </summary>
            LeftShift = GLFW_KEY_LEFT_SHIFT,
            /// <summary>
            /// Right SHIFT key.
            /// </summary>
            RightShift = GLFW_KEY_RIGHT_SHIFT,
            /// <summary>
            /// Left CONTROL key.
            /// </summary>
            LeftControl = GLFW_KEY_LEFT_CONTROL,
            /// <summary>
            /// Right CONTROL key.
            /// </summary>
            RightControl = GLFW_KEY_RIGHT_CONTROL,
            /// <summary>
            /// Left ALT key.
            /// </summary>
            LeftAlt = GLFW_KEY_LEFT_ALT,
            /// <summary>
            /// Right ALT key.
            /// </summary>
            RightAlt = GLFW_KEY_RIGHT_ALT,
            /// <summary>
            /// Browser Back key.
            /// </summary>
            // BrowserBack = 166,
            /// <summary>
            /// Browser Forward key.
            /// </summary>
            // BrowserForward = 167,
            /// <summary>
            /// Browser Refresh key.
            /// </summary>
            // BrowserRefresh = 168,
            /// <summary>
            /// Browser Stop key.
            /// </summary>
            // BrowserStop = 169,
            /// <summary>
            /// Browser Search key.
            /// </summary>
            // BrowserSearch = 170,
            /// <summary>
            /// Browser Favorites key.
            /// </summary>
            // BrowserFavorites = 171,
            /// <summary>
            /// Browser Start and Home key.
            /// </summary>
            // BrowserHome = 172,
            /// <summary>
            /// Volume Mute key.
            /// </summary>
            // VolumeMute = 173,
            /// <summary>
            /// Volume Down key.
            /// </summary>
            // VolumeDown = 174,
            /// <summary>
            /// Volume Up key.
            /// </summary>
            // VolumeUp = 175,
            /// <summary>
            /// Next Track key.
            /// </summary>
            // MediaNextTrack = 176,
            /// <summary>
            /// Previous Track key.
            /// </summary>
            // MediaPreviousTrack = 177,
            /// <summary>
            /// Stop Media key.
            /// </summary>
            // MediaStop = 178,
            /// <summary>
            /// Play/Pause Media key.
            /// </summary>
            // MediaPlayPause = 179,
            /// <summary>
            /// Start Mail key.
            /// </summary>
            // LaunchMail = 180,
            /// <summary>
            /// Select Media key.
            /// </summary>
            // SelectMedia = 181,
            /// <summary>
            /// Start Application 1 key.
            /// </summary>
            // LaunchApplication1 = 182,
            /// <summary>
            /// Start Application 2 key.
            /// </summary>
            // LaunchApplication2 = 183,
            /// <summary>
            /// The OEM Semicolon key on a US standard keyboard.
            /// </summary>
            OemSemicolon = GLFW_KEY_SEMICOLON,
            /// <summary>
            /// For any country/region, the '+' key.
            /// </summary>
            // OemPlus = 187,
            /// <summary>
            /// For any country/region, the ',' key.
            /// </summary>
            // OemComma = 188,
            /// <summary>
            /// For any country/region, the '-' key.
            /// </summary>
            // OemMinus = 189,
            /// <summary>
            /// For any country/region, the '.' key.
            /// </summary>
            OemPeriod = GLFW_KEY_PERIOD,
            /// <summary>
            /// The OEM question mark key on a US standard keyboard.
            /// </summary>
            // OemQuestion = 191,
            /// <summary>
            /// The OEM tilde key on a US standard keyboard.
            /// </summary>
            // OemTilde = 192,
            /// <summary>
            /// The OEM open bracket key on a US standard keyboard.
            /// </summary>
            // OemOpenBrackets = 219,
            /// <summary>
            /// The OEM pipe key on a US standard keyboard.
            /// </summary>
            // OemPipe = 220,
            /// <summary>
            /// The OEM close bracket key on a US standard keyboard.
            /// </summary>
            // OemCloseBrackets = 221,
            /// <summary>
            /// The OEM singled/double quote key on a US standard keyboard.
            /// </summary>
            // OemQuotes = 222,
            /// <summary>
            /// Used for miscellaneous characters; it can vary by keyboard.
            /// </summary>
            // Oem8 = 223,
            /// <summary>
            /// The OEM angle bracket or backslash key on the RT 102 key keyboard.
            /// </summary>
            OemBackslash = GLFW_KEY_BACKSLASH,
            /// <summary>
            /// IME PROCESS key.
            /// </summary>
            // ProcessKey = 229,
            /// <summary>
            /// Attn key.
            /// </summary>
            // Attn = 246,
            /// <summary>
            /// CrSel key.
            /// </summary>
            // Crsel = 247,
            /// <summary>
            /// ExSel key.
            /// </summary>
            // Exsel = 248,
            /// <summary>
            /// Erase EOF key.
            /// </summary>
            // EraseEof = 249,
            /// <summary>
            /// Play key.
            /// </summary>
            // Play = 250,
            /// <summary>
            /// Zoom key.
            /// </summary>
            // Zoom = 251,
            /// <summary>
            /// PA1 key.
            /// </summary>
            // Pa1 = 253,
            /// <summary>
            /// CLEAR key.
            /// </summary>
            // OemClear = 254,
            /// <summary>
            /// Green ChatPad key.
            /// </summary>
            // ChatPadGreen = 0xCA,
            /// <summary>
            /// Orange ChatPad key.
            /// </summary>
            ChatPadOrange = 0xCB,
            /// <summary>
            /// PAUSE key.
            /// </summary>
            Pause = GLFW_KEY_PAUSE,
            /// <summary>
            /// IME Convert key.
            /// </summary>
            // ImeConvert = 0x1c,
            /// <summary>
            /// IME NoConvert key.
            /// </summary>
            // ImeNoConvert = 0x1d,
            /// <summary>
            /// Kana key on Japanese keyboards.
            /// </summary>
            // Kana = 0x15,
            /// <summary>
            /// Kanji key on Japanese keyboards.
            /// </summary>
            // Kanji = 0x19,
            /// <summary>
            /// OEM Auto key.
            /// </summary>
            // OemAuto = 0xf3,
            /// <summary>
            /// OEM Copy key.
            /// </summary>
            // OemCopy = 0xf2,
            /// <summary>
            /// OEM Enlarge Window key.
            /// </summary>
            // OemEnlW = 0xf4
        };
    }
}

#endif // KEYS_HPP
