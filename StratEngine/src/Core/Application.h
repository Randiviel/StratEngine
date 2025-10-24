#pragma once
#include <memory>
#include "Window/WindowsWindow/WindowsWindow.h"
#include "Layer.h"
#include "Renderer/Camera.h"
#include "Scene/Scene.h"

namespace StratEngine {

    class Application {
        public:
            Application();
            ~Application();

            void Run();
            void OnEvent(Event& e);
            inline WindowsWindow* GetWindow() { return m_Window.get(); } ;
            inline LayerStack* GetLayerStack() { return &m_LayerStack; } ;  
            inline Renderer& GetRenderer() { return *m_Renderer; } ;
            inline SceneManager* GetSceneManager() { return &m_SceneManager; };
        private:
            std::unique_ptr<WindowsWindow> m_Window;
            LayerStack m_LayerStack;
            std::unique_ptr<Renderer> m_Renderer;
            SceneManager m_SceneManager;
            float m_DeltaTime;
            float m_LastFrame = 0.0f;
            bool m_MouseLock = false;
        private:
            bool isRunning();
            void CheckInput();
            void CalculateDeltaTime();
    };

    Application* CreateApplication();
    
}   