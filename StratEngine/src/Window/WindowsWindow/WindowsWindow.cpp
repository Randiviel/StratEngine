#include "pchstrat.h"
#include "WindowsWindow.h"

namespace StratEngine {
    WindowsWindow::WindowsWindow(const WindowProp& prop){
        if (!glfwInit()) 
        exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        m_WindowHandle = glfwCreateWindow(prop.height, prop.width, prop.name, NULL, NULL);
        if (!m_WindowHandle)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetKeyCallback(m_WindowHandle, key_callback);
        glfwMakeContextCurrent(m_WindowHandle);
        glfwSwapInterval(1);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
            }    
    }

    WindowsWindow::~WindowsWindow(){
        glfwDestroyWindow(m_WindowHandle);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

    void WindowsWindow::SetWindowSize()
    {
    }

    void WindowsWindow::GetWindowSize()
    {
    }

    GLFWwindow* WindowsWindow::GetWindowHandle()
    {
        return m_WindowHandle;
    }

    void WindowsWindow::OnEvent(Event &event)
    {
    }

    void WindowsWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

        window = glfwGetCurrentContext();
        
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    }
}
