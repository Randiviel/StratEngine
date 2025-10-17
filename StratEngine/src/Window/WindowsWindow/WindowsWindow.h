#pragma once

#include "Window/Window.h"
#include <functional>

struct GLFWwindow;

namespace StratEngine {

    class WindowsWindow : public Window{
        public:
        WindowsWindow(const WindowProp& prop);
        ~WindowsWindow();

        virtual void SetWindowSize() override;
        virtual void GetWindowSize() override;
        void HideCursor(bool option);
        void SetEventCallback(std::function<void(Event& e)> callback);

        GLFWwindow* GetWindowHandle();
        
        private:
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mousepos_callback(GLFWwindow* window, double xpos, double ypos);
        static void mousebutton_callback(GLFWwindow* window, int button, int action, int mods);
        static void window_size_callback(GLFWwindow* window, int width, int height);
        std::function<void(Event& e)> m_EventCallback;
        GLFWwindow* m_WindowHandle;

    };

}
