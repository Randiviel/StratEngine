#pragma once
#include "StratEngine.h"

class EditorLayer : public StratEngine::Layer {
    public:
        EditorLayer(StratEngine::Application* app);
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        inline void SetWindowHandle(GLFWwindow* windowhandle) { m_WindowHandle = windowhandle; };
    private:
        virtual void OnUpdate(float deltaTime) override;
        virtual void OnEvent(StratEngine::Event& event) override;
    private:
        GLFWwindow* m_WindowHandle;
        StratEngine::Application* m_App;
        bool m_ToolActive = true;
        bool m_FirstLaunch = true;
};