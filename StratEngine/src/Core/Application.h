#pragma once
#include <memory>
#include "Window/WindowsWindow/WindowsWindow.h"

namespace StratEngine {
    
    class Application {
        public:
            Application();
            ~Application();
            inline WindowsWindow* GetWindow() { return m_Window.get(); } ;
            void Run();
        private:
            std::unique_ptr<WindowsWindow> m_Window;

        private:
            bool isRunning();
    };

    Application* CreateApplication();
}   