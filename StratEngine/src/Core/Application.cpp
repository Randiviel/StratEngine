#include "pchstrat.h"
#include "StratConfig.h"

namespace StratEngine{
    Application::Application()
    {
        m_Window = std::make_unique<WindowsWindow>(WindowProp{StratConfig::WINDOW_TITLE, StratConfig::WINDOW_HEIGHT, StratConfig::WINDOW_WIDTH});
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

    bool Application::isRunning()
    {
        return (!glfwWindowShouldClose(m_Window->GetWindowHandle()));
    }
}

