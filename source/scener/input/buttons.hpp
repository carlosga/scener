// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_INPUT_BUTTONS_HPP
#define SCENER_INPUT_BUTTONS_HPP

#include <cstdint>

namespace scener::input
{
    /// Input device buttons.
    enum class buttons : std::uint32_t
    {
        DPadUp               = 1            ///< Directional pad up.
      , DPadDown             = 2            ///< Directional pad down.
      , DPadLeft             = 4            ///< Directional pad left.
      , DPadRight            = 8            ///< Directional pad right.
      , Start                = 16           ///< START button.
      , Back                 = 32           ///< BACK button.
      , LeftStick            = 64           ///< Left stick button (pressing the left stick).
      , RightStick           = 128          ///< Right stick button (pressing the right stick).
      , LeftShoulder         = 256          ///< Left bumper (shoulder) button.
      , RightShoulder        = 512          ///< Right bumper (shoulder) button.
      , BigButton            = 2048         ///< Big button.
      , A                    = 4096         ///< A button.
      , B                    = 8192         ///< B button.
      , X                    = 16384        ///< X button.
      , Y                    = 32768        ///< Y button.
      , LeftThumbstickLeft   = 2097152      ///< Left stick is towards the left.
      , RightTrigger         = 4194304      ///< Right trigger.
      , LeftTrigger          = 8388608      ///< Left trigger.
      , RightThumbstickUp    = 16777216     ///< Right stick is towards up.
      , RightThumbstickDown  = 33554432     ///< Right stick is towards down.
      , RightThumbstickRight = 67108864     ///< Right stick is towards the right.
      , RightThumbstickLeft  = 134217728    ///< Right stick is towards the left.
      , LeftThumbstickUp     = 268435456    ///< Left stick is towards up.
      , LeftThumbstickDown   = 536870912    ///< Left stick is towards down.
      , LeftThumbstickRight  = 1073741824   ///< Left stick is towards the right.
    };

    inline constexpr buttons operator&(const buttons& left, const buttons& right)
    {
        return static_cast<buttons>(static_cast<std::uint32_t>(left) & static_cast<std::uint32_t>(right));
    }

    inline constexpr buttons operator|(const buttons& left, const buttons& right)
    {
        return static_cast<buttons>(static_cast<std::uint32_t>(left) | static_cast<std::uint32_t>(right));
    }

    inline constexpr buttons operator~(const buttons& value)
    {
        return static_cast<buttons>(~static_cast<std::uint32_t>(value));
    }

    inline constexpr bool operator==(const buttons& left, const std::uint32_t& right)
    {
        return (static_cast<std::uint32_t>(left) == right);
    }

    inline constexpr bool operator!=(const buttons& left, const std::uint32_t& right)
    {
        return (static_cast<std::uint32_t>(left) != right);
    }

    inline buttons& operator&=(buttons& left, const buttons& right)
    {
        left = left & right;

        return left;
    }

    inline buttons& operator|=(buttons& left, const buttons& right)
    {
        left = left | right;

        return left;
    }
}

#endif  // SCENER_INPUT_BUTTONS_HPP
