#ifndef MOUSE_STATE_HPP
#define MOUSE_STATE_HPP

#include <cstdint>

#include <Input/Buttons.hpp>
#include <Input/ButtonState.hpp>

namespace SceneR
{
    namespace Input
    {
        // Represents the state of a mouse input device, including mouse cursor position and buttons pressed.
        struct MouseState
        {
        public:
            MouseState();

            //Initializes a new instance of the MouseState class.
            MouseState(const int& x
                     , const int& y
                     , const int& scrollWheel
                     , const ButtonState& leftButton
                     , const ButtonState& middleButton
                     , const ButtonState& rightButton
                     , const ButtonState& xButton1
                     , const ButtonState& xButton2);

            ~MouseState();

            // Returns the state of the left mouse button.
            const ButtonState& LeftButton() const;

            // Returns the state of the middle mouse button.
            const ButtonState& MiddleButton() const;

            // Returns the state of the right mouse button.
            const ButtonState& RightButton() const;

            // Gets the cumulative mouse scroll wheel value since the game was started.
            int ScrollWheelValue() const;

            // Specifies the horizontal position of the mouse cursor.
            int X() const;

            // Returns the state of XBUTTON1.
            const ButtonState& XButton1() const;

            // Returns the state of XBUTTON2.
            const ButtonState& XButton2() const;

            // Specifies the vertical position of the mouse cursor.
            int Y() const;

            // Determines whether two MouseState instances are equal.
            // public static bool op_Equality (MouseState left,MouseState right)

            // Determines whether two MouseState instances are not equal.
            // public static bool op_Inequality (MouseState left,MouseState right)

        private:
            int         _x;
            int         _y;
            int         _scrollWheel;
            ButtonState _leftButton;
            ButtonState _middleButton;
            ButtonState _rightButton;
            ButtonState _xButton1;
            ButtonState _xButton2;
        };
    }
}

#endif // MOUSE_HPP
