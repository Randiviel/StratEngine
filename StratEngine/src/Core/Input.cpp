#include "pchstrat.h"
#include "StratConfig.h"

namespace StratEngine
{
    std::array<bool, Input::MAX_KEYS> Input::s_Keys = {};
    std::array<bool, Input::MAX_MOUSE_BUTTONS> Input::s_MouseButtons = {};
    float Input::s_MouseX = 0.0f;
    float Input::s_MouseY = 0.0f;

    bool Input::IsKeyPressed(int keycode)
    {
        if(keycode < 0 | keycode >= MAX_KEYS)
            return false;

        return s_Keys[keycode];
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        if(button < 0 | button >= MAX_MOUSE_BUTTONS)
            return false;

        return s_MouseButtons[button];
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        return std::pair<float, float>(s_MouseX, s_MouseY);
    }

    void Input::UpdateKeyState(int keycode, bool pressed)
    {
        if(keycode < 0 | keycode >= MAX_KEYS)
            return;

        s_Keys[keycode] = pressed;
    }

    void Input::UpdateMouseButtonState(int button, bool pressed)
    {
        if(button < 0 | button >= MAX_KEYS)
            return;
        s_MouseButtons[button] = pressed;
    }

    void Input::UpdateMousePosition(float x, float y)
    {
        s_MouseX = x;
        s_MouseY = y;
    }
}