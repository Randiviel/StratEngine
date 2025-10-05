#pragma once
#include <memory>
#include "Window/WindowsWindow/WindowsWindow.h"
#include "Layer.h"
#include "Renderer/Camera.h"

namespace StratEngine {

    enum class RenderAPI {
        None = 0, OpenGL = 1
    };
    
    class Application {
        public:
            Application();
            ~Application();

            void Run();
            void OnEvent(Event& e);
            inline WindowsWindow* GetWindow() { return m_Window.get(); } ;
            inline RenderAPI GetRenderAPI() const { return m_RenderAPI; } ;
       
        private:
            std::unique_ptr<WindowsWindow> m_Window;
            LayerStack m_LayerStack;
            RenderAPI m_RenderAPI = RenderAPI::OpenGL;
            Camera m_Camera;
            float m_DeltaTime;
        private:
            bool isRunning();
    };

    Application* CreateApplication();
}   