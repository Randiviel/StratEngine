#include "StratEngine.h"
#include "EditorLayer/EditorLayer.h"

StratEngine::Application* StratEngine::CreateApplication(){
    Application* app = new Application();
    EditorLayer* editor = new EditorLayer();
    editor->SetWindowHandle(app->GetWindow()->GetWindowHandle());
    editor->OnAttach();
    app->GetLayerStack()->PushLayer(editor);
    return app;
}