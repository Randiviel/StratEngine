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
        unsigned int indices[] = {  
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };
        glEnable(GL_DEPTH_TEST);  
        std::vector<ShaderAttributes> layout = {
            {"a_Position", ShaderAttribTypes::Float3, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float3), 3, false},
            {"a_Texture", ShaderAttribTypes::Float2, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float2), 2, false}
        };
        Shader shader("Shaders/SandBoxShader.glsl"); 
        float lastFrame = 0.0f;

        while (isRunning())
        {   
            
            float currentFrame = glfwGetTime();
            m_DeltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;  
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_W) == GLFW_PRESS)
                    m_Camera.MoveCamera(CameraMovement::FORWARD, m_DeltaTime);
                if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_S) == GLFW_PRESS)
                    m_Camera.MoveCamera(CameraMovement::BACKWARD, m_DeltaTime);
                if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_A) == GLFW_PRESS)
                    m_Camera.MoveCamera(CameraMovement::LEFT, m_DeltaTime);
                if (glfwGetKey(m_Window->GetWindowHandle(), GLFW_KEY_D) == GLFW_PRESS)
        m_Camera.MoveCamera(CameraMovement::RIGHT, m_DeltaTime);
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate(0.0f);
            }
            
            glUseProgram(shader.GetShader());
            // create transformations
            glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            glm::mat4 view          = m_Camera.GetViewMatrix();
            glm::mat4 projection    = glm::mat4(1.0f);
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
            view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            projection = glm::perspective(glm::radians(45.0f), (float)StratConfig::WINDOW_HEIGHT / (float)StratConfig::WINDOW_WIDTH, 0.1f, 100.0f);
            // retrieve the matrix uniform locations
            unsigned int modelLoc = glGetUniformLocation(shader.GetShader(), "model");
            unsigned int viewLoc  = glGetUniformLocation(shader.GetShader(), "view");
            // pass them to the shaders (3 different ways)
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            shader.setMat4("projection", projection);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
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
            m_Camera.ProcessMouseMovement(mouseX, mouseY);
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

