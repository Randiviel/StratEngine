#pragma once
#include "StratEngine.h"

class EditorLayer : public StratEngine::Layer {
    public:
        EditorLayer(StratEngine::Application* app);
        virtual void OnAttach() override;
        virtual void OnDetach() override;
    private:
        virtual void OnUpdate(float deltaTime) override;
        virtual void OnEvent(StratEngine::Event& event) override;
        void MainWindow();
        void Viewport();
        void EntityProperties();
        void SetupDockspace();
        void AssetManager();
        void Objects();

    private:
        StratEngine::Application* m_App;
        ImGuiID m_DockSpaceID;
        bool m_ToolActive = true;
        bool m_FirstLaunch = true;
};