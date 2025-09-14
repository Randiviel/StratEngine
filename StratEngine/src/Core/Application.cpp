#include "pchstrat.h"
#include "StratConfig.h"
#include "Application.h"

namespace StratEngine{
    Application::Application()
    {
        m_Window = std::make_unique<WindowsWindow>(WindowProp{StratConfig::WINDOW_TITLE, StratConfig::WINDOW_HEIGHT, StratConfig::WINDOW_WIDTH});
        m_Window->SetEventCallback([this](Event& e) {OnEvent(e);});
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        while (isRunning())
        {      

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);


            glfwSwapBuffers(m_Window->GetWindowHandle());
            glfwPollEvents();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher Dispatcher(e);

        Dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e){
            std::cout << StratEngine::KeyCodeToString(e.GetKey()) << " " << e.GetKey() << "\n";
        });
    }

    bool Application::isRunning()
    {
        return (!glfwWindowShouldClose(m_Window->GetWindowHandle()));
    }
}

