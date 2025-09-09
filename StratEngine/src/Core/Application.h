#pragma once
#include <memory>
#include "Window/WindowsWindow/WindowsWindow.h"

namespace StratEngine {
    class Application {
        public:
            Application();
            ~Application();
            inline WindowsWindow* GetWindow() { return m_WindowClass.get(); } ;
        private:
            std::unique_ptr<WindowsWindow> m_WindowClass;
    };

    Application* CreateApplication();
}   