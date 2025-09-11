#pragma once

#include "Window/Window.h"

struct GLFWwindow;

namespace StratEngine {

    class WindowsWindow : public Window{
        public:
        WindowsWindow(const WindowProp& prop);
        ~WindowsWindow();

        virtual void SetWindowSize() override;
        virtual void GetWindowSize() override;
        virtual void OnEvent(Event& event) override;

        GLFWwindow* GetWindowHandle();
        
        private:
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        GLFWwindow* m_WindowHandle;

    };

}
