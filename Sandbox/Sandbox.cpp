#include "StratEngine.h"

class SandboxLayer : public StratEngine::Layer {
        virtual void OnAttach() override
        {

        }
        virtual void OnDetach() override
        {

        }
        virtual void OnUpdate(float deltaTime) override
        {
            
        }
        virtual void OnEvent(StratEngine::Event& event) override
        {

        }
};

StratEngine::Application* StratEngine::CreateApplication(){
    Application* app = new Application();
    app->GetLayerStack()->PushLayer(new SandboxLayer);
    return app;
}