#include "pchstrat.h"
#include "StratConfig.h"

namespace StratEngine{

    Application::Application()
    {
        if(m_RenderAPI == RenderAPI::OpenGL)
        {
            std::cout << "RenderAPI: OpenGL\n";
            m_Window = std::make_unique<WindowsWindow>(WindowProp{StratConfig::WINDOW_TITLE, StratConfig::WINDOW_HEIGHT, StratConfig::WINDOW_WIDTH});
            m_Window->SetEventCallback([this](Event& e) {OnEvent(e);});
        }
        else
            std::cout << "RenderAPI: None\n";

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {

        float vertices[] = {
            0.25f,  0.5f, 0.0f,  // top right
            0.25f, -0.25f, 0.0f,  // bottom right
            -0.25f, -0.25f, 0.0f,  // bottom left
            -0.25f,  0.25f, 0.0f   // top left 
            };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
            };

        VertexArray VAO;
        VertexBuffer VBO(vertices, sizeof(vertices));
        VAO.AddBuffer(VBO);
        Shader Shader("Shaders/SandBoxShader.glsl");

        while (isRunning())
        {      

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate(0.0f);
            }

            glUseProgram(Shader.GetShader());
            VAO.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
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

        Dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& e){
            auto mousepos = e.GetMousePos();
        });

        Dispatcher.Dispatch<MousePressedEvent>([this](MousePressedEvent& e){
            int mousebutton = e.GetMouseButton();
            std::cout << "MouseButtonPressed: " << mousebutton << '\n';
        });
    }

    bool Application::isRunning()
    {
        return (!glfwWindowShouldClose(m_Window->GetWindowHandle()));
    }
}

