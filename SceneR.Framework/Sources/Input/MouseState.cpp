#include <Input/MouseState.hpp>

namespace SceneR
{
    namespace Input
    {
        MouseState::MouseState()
        {
        }

        MouseState::MouseState(const int& x
                             , const int& y
                             , const int& scrollWheel
                             , const ButtonState& leftButton
                             , const ButtonState& middleButton
                             , const ButtonState& rightButton
                             , const ButtonState& xButton1
                             , const ButtonState& xButton2)
        {
            _x            = x;
            _y            = y;
            _scrollWheel  = scrollWheel;
            _leftButton   = leftButton;
            _middleButton = middleButton;
            _rightButton  = rightButton;
            _xButton1     = xButton1;
            _xButton2     = xButton2;
        }

        MouseState::~MouseState()
        {
        }

        // Returns the state of the left mouse button.
        const ButtonState& MouseState::LeftButton() const
        {
            return _leftButton;
        }

        // Returns the state of the middle mouse button.
        const ButtonState& MouseState::MiddleButton() const
        {
            return _middleButton;
        }

        // Returns the state of the right mouse button.
        const ButtonState& MouseState::RightButton() const
        {
            return _rightButton;
        }

        // Gets the cumulative mouse scroll wheel value since the game was started.
        int MouseState::ScrollWheelValue() const
        {
            return _scrollWheel;
        }

        // Specifies the horizontal position of the mouse cursor.
        int MouseState::X() const
        {
            return _x;
        }

        // Returns the state of XBUTTON1.
        const ButtonState& MouseState::XButton1() const
        {
            return _xButton1;
        }

        // Returns the state of XBUTTON2.
        const ButtonState& MouseState::XButton2() const
        {
            return _xButton2;
        }

        // Specifies the vertical position of the mouse cursor.
        int MouseState::Y() const
        {
            return _y;
        }
    }
}
