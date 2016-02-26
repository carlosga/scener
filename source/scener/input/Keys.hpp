// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_KEYS_HPP
#define SCENER_INPUT_KEYS_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace scener { namespace input {

/// Identifies a particular key on a keyboard.
enum class Keys : std::uint32_t
{
    none            = 0     ///< Reserved.
  , Back            = 1     ///< BACKSPACE key.
  , Tab             = 2     ///< TAB key.
  , Enter           = 3     ///< ENTER key.
  , CapsLock        = 4     ///< CAPS LOCK key.
  , Escape          = 5     ///< ESC key.
  , Space           = 6     ///< SPACEBAR key.
  , PageUp          = 7     ///< PAGE UP key.
  , PageDown        = 8     ///< PAGE DOWN key.
  , End             = 9     ///< END key.
  , Home            = 10    ///< HOME key.
  , Left            = 11    ///< LEFT ARROW key.
  , Up              = 12    ///< UP ARROW key.
  , Right           = 13    ///< RIGHT ARROW key.
  , Down            = 14    ///< DOWN ARROW key.
  , PrintScreen     = 15    ///< PRINT SCREEN key.
  , Insert          = 16    ///< INS key.
  , Delete          = 17    ///< DEL key.
  , A               = 65    ///< A key.
  , B               = 66    ///< B key.
  , C               = 67    ///< C key.
  , D               = 68    ///< D key.
  , E               = 69    ///< E key.
  , F               = 70    ///< F key.
  , G               = 71    ///< G key.
  , H               = 72    ///< H key.
  , I               = 73    ///< I key.
  , J               = 74    ///< J key.
  , K               = 75    ///< K key.
  , L               = 76    ///< L key.
  , M               = 77    ///< M key.
  , N               = 78    ///< N key.
  , O               = 79    ///< O key.
  , P               = 80    ///< P key.
  , Q               = 81    ///< Q key.
  , R               = 82    ///< R key.
  , S               = 83    ///< S key.
  , T               = 84    ///< T key.
  , U               = 85    ///< U key.
  , V               = 86    ///< V key.
  , W               = 87    ///< W key.
  , X               = 88    ///< X key.
  , Y               = 89    ///< Y key.
  , Z               = 90    ///< Z key.
  , NumPad0         = 18    ///< Numeric keypad 0 key.
  , NumPad1         = 19    ///< Numeric keypad 1 key.
  , NumPad2         = 20    ///< Numeric keypad 2 key.
  , NumPad3         = 21    ///< Numeric keypad 3 key.
  , NumPad4         = 22    ///< Numeric keypad 4 key.
  , NumPad5         = 23    ///< Numeric keypad 5 key.
  , NumPad6         = 24    ///< Numeric keypad 6 key.
  , NumPad7         = 25    ///< Numeric keypad 7 key.
  , NumPad8         = 26    ///< Numeric keypad 8 key.
  , NumPad9         = 27    ///< Numeric keypad 9 key.
  , Multiply        = 28    ///< Multiply key.
  , Add             = 29    ///< Add key.
  , Subtract        = 30    ///< Subtract key.
  , Decimal         = 31    ///< Decimal key.
  , Divide          = 32    ///< Divide key.
  , F1              = 33    ///< F1 key.
  , F2              = 34    ///< F2 key.
  , F3              = 35    ///< F3 key.
  , F4              = 36    ///< F4 key.
  , F5              = 37    ///< F5 key.
  , F6              = 38    ///< F6 key.
  , F7              = 39    ///< F7 key.
  , F8              = 40    ///< F8 key.
  , F9              = 41    ///< F9 key.
  , F10             = 42    ///< F10 key.
  , F11             = 43    ///< F11 key.
  , F12             = 44    ///< F12 key.
  , F13             = 45    ///< F13 key.
  , F14             = 46    ///< F14 key.
  , F15             = 47    ///< F15 key.
  , F16             = 48    ///< F16 key.
  , F17             = 49    ///< F17 key.
  , F18             = 50    ///< F18 key.
  , F19             = 51    ///< F19 key.
  , F20             = 52    ///< F20 key.
  , F21             = 53    ///< F21 key.
  , F22             = 54    ///< F22 key.
  , F23             = 55    ///< F23 key.
  , F24             = 56    ///< F24 key.
  , NumLock         = 57    ///< NUM LOCK key.
  , Scroll          = 58    ///< SCROLL LOCK key.
  , LeftShift       = 59    ///< Left SHIFT key.
  , RightShift      = 60    ///< Right SHIFT key.
  , LeftControl     = 61    ///< Left CONTROL key.
  , RightControl    = 62    ///< Right CONTROL key.
  , LeftAlt         = 63    ///< Left ALT key.
  , RightAlt        = 64    ///< Right ALT key.
  , OemSemicolon    = 91    ///< The OEM Semicolon key on a US standard keyboard.
  , OemPeriod       = 92    ///< For any country/region the '.' key.
  , OemBackslash    = 93    ///< The OEM angle bracket or backslash key on the RT 102 key keyboard.
  , Pause           = 94    ///< PAUSE key.
};

}}

#endif // SCENER_INPUT_KEYS_HPP
