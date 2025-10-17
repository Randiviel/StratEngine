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
        float lastFrame = 0.0f;

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

        Shader shader("Shaders/SandBoxShader.glsl");
        auto renderer = std::make_unique<OpenGL_Renderer>();
        renderer->SetShader(shader);

        std::vector<ShaderAttributes> layout = {
        {"a_Position", ShaderAttribTypes::Float3, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float3), 3, false},
        {"a_Texture", ShaderAttribTypes::Float2, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float2), 2, false}
        };

        Scene myScene("myScene");
        Model myModel("myModel");
        Mesh myCube("myCube", vertices, layout, "Textures/Container.jpg");
        myModel.AddMesh(myCube);
        myScene.AddModel(myModel);
        myScene.AddRenderer(std::move(renderer));
        m_CurrentScene = &myScene;

        while (isRunning())
        {             
            CheckInput();
            // DeltaTime
            float currentFrame = glfwGetTime();
            m_DeltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;  
            // Background Color
            m_CurrentScene->Render();
            glfwSwapBuffers(m_Window->GetWindowHandle());
            glfwPollEvents();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher Dispatcher(e);

        // Dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e){
        //     std::cout << StratEngine::KeyCodeToString(e.GetKey()) << " " << e.GetKey() << "\n";
        //     if(StratEngine::KeyCodeToString(e.GetKey()) == "W")
        //     {
        //         m_Camera.MoveCamera(CameraMovement::FORWARD, m_DeltaTime);
        //     }
        //     if(StratEngine::KeyCodeToString(e.GetKey()) == "S")
        //     {
        //         m_Camera.MoveCamera(CameraMovement::BACKWARD, m_DeltaTime);
        //     }
        //     if(StratEngine::KeyCodeToString(e.GetKey()) == "D")
        //     {
        //         m_Camera.MoveCamera(CameraMovement::RIGHT, m_DeltaTime);
        //     }
        //     if(StratEngine::KeyCodeToString(e.GetKey()) == "A")
        //     {
        //         m_Camera.MoveCamera(CameraMovement::LEFT, m_DeltaTime);
        //     }
        // });

        Dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& e){
            auto mousepos = e.GetMousePos();
            float mouseX = static_cast<float>(mousepos.first);
            float mouseY = static_cast<float>(mousepos.second);
            m_CurrentScene->GetCamera().ProcessMouseMovement(mouseX, mouseY);
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

    void Application::CheckInput()
    {
        if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_W) == GLFW_PRESS)
                m_CurrentScene->GetCamera().MoveCamera(CameraMovement::FORWARD, m_DeltaTime);
        if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_S) == GLFW_PRESS)
                m_CurrentScene->GetCamera().MoveCamera(CameraMovement::BACKWARD, m_DeltaTime);
        if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_A) == GLFW_PRESS)
                m_CurrentScene->GetCamera().MoveCamera(CameraMovement::LEFT, m_DeltaTime);
        if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_D) == GLFW_PRESS)
                m_CurrentScene->GetCamera().MoveCamera(CameraMovement::RIGHT, m_DeltaTime);
    }
}

