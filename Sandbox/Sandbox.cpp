#include "StratEngine.h"
#include "StratEngineCore.h"
#include "EditorLayer/EditorLayer.h"


StratEngine::Application* StratEngine::CreateApplication(){
    Application* app = new Application();
    EditorLayer* editor = new EditorLayer(app);
    editor->SetWindowHandle(app->GetWindow()->GetWindowHandle());
    editor->OnAttach();
    app->GetLayerStack()->PushLayer(editor);
    return app;
}