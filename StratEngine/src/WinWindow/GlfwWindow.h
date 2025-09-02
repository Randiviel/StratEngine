#pragma once
#include <functional>
#include "Event/Event.h"

struct GLFWwindow;

namespace StratEngine {

    class WinWindow{
    public:
        WinWindow();
        ~WinWindow();
        inline GLFWwindow* GetWindowHandle() const { return m_Window; }
        void BeginFrame();
        void EndFrame();

        void SetEventCallback(std::function<void(Event&)> callback) { 
            m_EventCallback = callback; 
        }

        GLFWwindow* GetWindowPointer() const { return m_Window; }

        private:
        std::function<void(Event&)> m_EventCallback;

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        GLFWwindow* m_Window;
    };
}