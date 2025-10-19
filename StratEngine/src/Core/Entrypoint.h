#pragma once
#include "pchstrat.h"

extern StratEngine::Application* StratEngine::CreateApplication();

int main()
{
    StratEngine::Log::Init();
    auto app = StratEngine::CreateApplication();
    app->Run();
}