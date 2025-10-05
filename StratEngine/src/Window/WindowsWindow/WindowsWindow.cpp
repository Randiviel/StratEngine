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

        glfwMakeContextCurrent(m_WindowHandle);
        glfwSetWindowUserPointer(m_WindowHandle, this);
        glfwSetKeyCallback(m_WindowHandle, key_callback);
        glfwSetCursorPosCallback(m_WindowHandle, mousepos_callback);
        glfwSetMouseButtonCallback(m_WindowHandle, mousebutton_callback);
        glfwSetWindowSizeCallback(m_WindowHandle, window_size_callback);
        glfwSetInputMode(m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

    void WindowsWindow::SetEventCallback(std::function<void(Event& e)> callback)
    {
        m_EventCallback = callback;
    }

    GLFWwindow* WindowsWindow::GetWindowHandle()
    {
        return m_WindowHandle;
    }

    void WindowsWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        WindowsWindow* windowInstance = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
        
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, GLFW_TRUE);

        if ((action == GLFW_PRESS || action == GLFW_REPEAT) && windowInstance->m_EventCallback) {
        KeyPressedEvent event(key);
        windowInstance->m_EventCallback(event);
        }

    }

    void WindowsWindow::mousepos_callback(GLFWwindow *window, double xpos, double ypos)
    {
        WindowsWindow* windowInstance = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
        MouseMovedEvent event(xpos, ypos);
        windowInstance->m_EventCallback(event);
    }
    void WindowsWindow::mousebutton_callback(GLFWwindow *window, int button, int action, int mods)
    {
        switch(action){
            case GLFW_PRESS: {
                WindowsWindow* windowInstance = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
                MousePressedEvent event(button);
                windowInstance->m_EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                break;
            }
        }
    }
    void WindowsWindow::window_size_callback(GLFWwindow *window, int width, int height)
    {
        WindowsWindow* windowInstance = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
        
    }
}
