#include "pchstrat.h"

namespace StratEngine {

    Application::Application()
    {
        m_WindowClass = std::make_unique<WinWindow>();  
        m_WindowClass->SetEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        m_ImGuiLayer = std::make_unique<UI_imgui>(m_WindowClass);

    }

    Application::~Application()
    {
        glfwTerminate();
    }

    void Application::onEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event){
            std::cout << "Key Pressed: " << StratEngine::KeyCodeToString(event.GetKey()) << std::endl;
            switch(event.GetKey()){
                case STRAT_KEY_ESCAPE:
                    m_Running = false;
                    break;
                default:
                    break;
            }
            return true;
        });
    }
    void Application::Run()
    {
        while (m_Running) {
            m_WindowClass->BeginFrame();
            // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            // glClear(GL_COLOR_BUFFER_BIT);
            m_ImGuiLayer->Begin();
            m_ImGuiLayer->End();
            // Main loop content
            m_WindowClass->EndFrame();
        }
    }
}