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

        std::vector<ShaderAttributes> layout = {
            {"a_Position", ShaderAttribTypes::Float3, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float3), 3, false},
            {"a_Texture", ShaderAttribTypes::Float2, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float2), 2, false}
        };
        Shader myShader("Shaders/SandBoxShader.glsl");
        m_Renderer->SetShader(myShader);
        auto& myScene = m_SceneManager.CreateScene("myScene");
        m_SceneManager.SetCurrentScene("myScene");
        Mesh mesh("MyCube", vertices, layout, "Textures/Container.jpg");
        Model model("MyModel");
        model.AddMesh(mesh);
        myScene.AddModel(model);


        while (isRunning())
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
            Input::UpdateKeyState(e.GetKey(), true);

            if(Input::IsKeyPressed(STRAT_KEY_LEFT_ALT))
            {
                if(m_MouseLock == true)
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

        Dispatcher.Dispatch<KeyReleasedEvent>([this](KeyReleasedEvent& e){
            Input::UpdateKeyState(e.GetKey(), false);
        });

        Dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& e){
            auto mousepos = e.GetMousePos();
            float mouseX = static_cast<float>(mousepos.first);
            float mouseY = static_cast<float>(mousepos.second);
            Input::UpdateMousePosition(mouseX, mouseY);
        });

        Dispatcher.Dispatch<MousePressedEvent>([this](MousePressedEvent& e){
            Input::UpdateKeyState(e.GetMouseButton(), true);
        });

        Dispatcher.Dispatch<MouseReleasedEvent>([this](MouseReleasedEvent& e){
            Input::UpdateKeyState(e.GetMouseButton(), false);
        });
    }

    bool Application::isRunning()
    {
        return (!glfwWindowShouldClose(m_Window->GetWindowHandle()));
    }

    void Application::CheckInput()
    {
        if(m_MouseLock)
        {
        if(Input::IsKeyPressed(STRAT_KEY_W))
                m_SceneManager.GetCurrentScene()->GetCamera().MoveCamera(CameraMovement::FORWARD, m_DeltaTime);
        if(Input::IsKeyPressed(STRAT_KEY_S))
                m_SceneManager.GetCurrentScene()->GetCamera().MoveCamera(CameraMovement::BACKWARD, m_DeltaTime);
        if(Input::IsKeyPressed(STRAT_KEY_A))
                m_SceneManager.GetCurrentScene()->GetCamera().MoveCamera(CameraMovement::LEFT, m_DeltaTime);
        if(Input::IsKeyPressed(STRAT_KEY_D))
                m_SceneManager.GetCurrentScene()->GetCamera().MoveCamera(CameraMovement::RIGHT, m_DeltaTime);
        
                auto mousePos = Input::GetMousePosition();
                m_SceneManager.GetCurrentScene()->GetCamera().ProcessMouseMovement(mousePos.first, mousePos.second);
        }
    }

    void Application::CalculateDeltaTime()
    {
            float currentFrame = glfwGetTime();
            m_DeltaTime = currentFrame - m_LastFrame;
            m_LastFrame = currentFrame;  
    }
}

            // if(StratEngine::KeyCodeToString(e.GetKey()) == "Left Alt")
            // {
            //     if(m_MouseLock)
            //     {
            //         m_MouseLock = false;
            //         m_Window->HideCursor(false);
            //     }
            //     else
            //     {
            //         m_MouseLock = true;
            //         m_Window->HideCursor(true);
            //     }
            // }