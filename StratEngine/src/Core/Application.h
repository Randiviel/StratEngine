#pragma once
#include <memory>
#include "Window/WindowsWindow/WindowsWindow.h"

namespace StratEngine {
    
    class Application {
        public:
            Application();
            ~Application();

            void Run();
            void OnEvent(Event& e);
            inline WindowsWindow* GetWindow() { return m_Window.get(); } ;

        private:
            std::unique_ptr<WindowsWindow> m_Window;

        private:
            bool isRunning();
    };

    Application* CreateApplication();
}   