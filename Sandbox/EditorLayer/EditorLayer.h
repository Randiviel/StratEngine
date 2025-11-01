#pragma once
#include "StratEngine.h"

struct EditorLayerInfo
{
    std::string SelectedEntity;
    ImGuiID DockSpaceID;
    bool ToolActive = true;
    bool FirstLaunch = true;
};

class EditorLayer : public StratEngine::Layer {
    public:
        EditorLayer(StratEngine::Application* app);
        virtual void OnAttach() override;
        virtual void OnDetach() override;
    private:
        virtual void OnUpdate(float deltaTime) override;
        virtual void OnEvent() override;
        void NewFrame();
        void EndFrame();
        // ImGuiWindows
        void MainWindow();
        void Viewport();
        void EntityProperties();
        void SetupDockspace();
        void AssetManager();
        void Objects();
        void CameraInput(float deltatime);

    private:
        StratEngine::Camera m_EditorCamera;
        StratEngine::Application* m_Engine;
        ImGuiID m_DockSpaceID;
        EditorLayerInfo m_EditorInfo;
};