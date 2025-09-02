#include "pchstrat.h"


namespace StratEngine {

    WinWindow::WinWindow() {
        if (!glfwInit()){
            exit(EXIT_FAILURE);
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        m_Window = glfwCreateWindow(StratConfig::WINDOW_HEIGHT, StratConfig::WINDOW_WIDTH, StratConfig::WINDOW_TITLE, nullptr, nullptr);
        glfwSetKeyCallback(m_Window, key_callback);
        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
        }

        glfwSetWindowUserPointer(m_Window, this);

    }

    WinWindow::~WinWindow() {
        glfwDestroyWindow(m_Window);
    }


    void WinWindow::BeginFrame()
    {
        glfwPollEvents();
    }

    void WinWindow::EndFrame()
    {
        glfwSwapBuffers(m_Window);
    }

    void WinWindow::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        WinWindow* win = static_cast<WinWindow*>(glfwGetWindowUserPointer(window));
        if (!win->m_EventCallback) return;

        switch(action){
            case GLFW_PRESS:
                {
                    KeyPressedEvent event(key);
                    win->m_EventCallback(event);
                    break;
                }
            case GLFW_RELEASE:
                {
                    
                    break;
                }
            case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key);
                    win->m_EventCallback(event);
                    break;
                }
        }

    }
}