#include "StratEngine.h"

StratEngine::Application* StratEngine::CreateApplication(){
    Application* app = new Application();
    return app;
}