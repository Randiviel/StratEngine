#pragma once

#include <array>

namespace StratEngine 
{
    class Input
    {
        public:
            static bool IsKeyPressed(int keycode);
            static bool IsMouseButtonPressed(int button);
            static std::pair<float, float> GetMousePosition();

            static void UpdateKeyState(int keycode, bool pressed);
            static void UpdateMouseButtonState(int button, bool pressed);
            static void UpdateMousePosition(float x, float y);

        private:
            static constexpr size_t MAX_KEYS = 512;
            static constexpr size_t MAX_MOUSE_BUTTONS = 8;
            
            static std::array<bool, MAX_KEYS> s_Keys;
            static std::array<bool, MAX_MOUSE_BUTTONS> s_MouseButtons;
            static float s_MouseX;
            static float s_MouseY;
    };
}