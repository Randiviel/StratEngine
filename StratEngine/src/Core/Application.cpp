#include "pchstrat.h"
#include "StratConfig.h"
#include "Application.h"

namespace StratEngine{

    Application::Application()
    {
        if(m_RenderAPI == RenderAPI::OpenGL)
        {
            m_Window = std::make_unique<WindowsWindow>(WindowProp{StratConfig::WINDOW_TITLE, StratConfig::WINDOW_HEIGHT, StratConfig::WINDOW_WIDTH});
            m_Window->SetEventCallback([this](Event& e) {OnEvent(e);});
            m_Window->HideCursor(true);
            m_Renderer = std::make_unique<OpenGL_Renderer>();
        }
        else
            std::cout << "RenderAPI: None\n";
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        std::vector<float> vertices = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        Shader myShader("Shaders/SandBoxShader.glsl");
        m_Renderer->SetShader(myShader);
        auto& myScene = m_SceneManager.CreateScene("myScene");
        m_SceneManager.SetCurrentScene("myScene");
        

        while (isRunning())
        {
            // Check Keyboard Input
            CheckInput();

            // DeltaTime
            CalculateDeltaTime();

            // Render Scene
            m_SceneManager.GetCurrentScene()->Render(*m_Renderer);

            // Update all Layers
            for(auto layer : m_LayerStack)
                layer->OnUpdate(m_DeltaTime);

            // Swap buffers
            glfwSwapBuffers(m_Window->GetWindowHandle());
            glfwPollEvents();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher Dispatcher(e);

        Dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e){
        std::cout << StratEngine::KeyCodeToString(e.GetKey()) << " " << e.GetKey() << "\n";
            if(StratEngine::KeyCodeToString(e.GetKey()) == "Left Alt")
            {
                if(m_MouseLock)
                {
                    m_MouseLock = false;
                    m_Window->HideCursor(false);
                }
                else
                {
                    m_MouseLock = true;
                    m_Window->HideCursor(true);
                }
            }
        });

        if(m_MouseLock)
        {
            Dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& e){
                auto mousepos = e.GetMousePos();
                float mouseX = static_cast<float>(mousepos.first);
                float mouseY = static_cast<float>(mousepos.second);
                m_SceneManager.GetCurrentScene()->GetCamera().ProcessMouseMovement(mouseX, mouseY);
            });

            Dispatcher.Dispatch<MousePressedEvent>([this](MousePressedEvent& e){
                int mousebutton = e.GetMouseButton();
                std::cout << "MouseButtonPressed: " << mousebutton << '\n';
            });
        }

    }

    bool Application::isRunning()
    {
        return (!glfwWindowShouldClose(m_Window->GetWindowHandle()));
    }

    void Application::CheckInput()
    {
        if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_W) == GLFW_PRESS)
                m_SceneManager.GetCurrentScene()->GetCamera().MoveCamera(CameraMovement::FORWARD, m_DeltaTime);
        if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_S) == GLFW_PRESS)
                m_SceneManager.GetCurrentScene()->GetCamera().MoveCamera(CameraMovement::BACKWARD, m_DeltaTime);
        if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_A) == GLFW_PRESS)
                m_SceneManager.GetCurrentScene()->GetCamera().MoveCamera(CameraMovement::LEFT, m_DeltaTime);
        if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_D) == GLFW_PRESS)
                m_SceneManager.GetCurrentScene()->GetCamera().MoveCamera(CameraMovement::RIGHT, m_DeltaTime);
    }

    void Application::CalculateDeltaTime()
    {
            float currentFrame = glfwGetTime();
            m_DeltaTime = currentFrame - m_LastFrame;
            m_LastFrame = currentFrame;  
    }
}

