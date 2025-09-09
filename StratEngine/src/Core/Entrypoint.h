#include "pchstrat.h"

extern StratEngine::Application* StratEngine::CreateApplication();

int main()
{
    auto app = StratEngine::CreateApplication();
    app->GetWindow()->Run();
}