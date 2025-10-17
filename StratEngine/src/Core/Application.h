#pragma once
#include <memory>
#include "Window/WindowsWindow/WindowsWindow.h"
#include "Layer.h"
#include "Renderer/Camera.h"
#include "Renderer/Scene.h"

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
            inline LayerStack* GetLayerStack() { return &m_LayerStack; } ;
       
        private:
            std::unique_ptr<WindowsWindow> m_Window;
            LayerStack m_LayerStack;
            RenderAPI m_RenderAPI = RenderAPI::OpenGL;
            Scene* m_CurrentScene;
            float m_DeltaTime;
            bool m_MouseLock = true;
        private:
            bool isRunning();
            void CheckInput();
    };

    Application* CreateApplication();
}   