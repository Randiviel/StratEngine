#include "pchstrat.h"
#include "StratConfig.h"

namespace StratEngine
{
    Shader::Shader(const char *vertexPath, const char *fragmentPath)
    {

    }

    Shader::Shader(const char *filepath)
    {

        std::ifstream shaderfile(filepath);
        if(!shaderfile.is_open())
        {
            std::cerr << "ERROR: Failed to open shader file: " << filepath << std::endl;
            m_ShaderID = 0; // Oznacz jako invalid
            return;
        }
        
        std::stringstream ss;
        ss << shaderfile.rdbuf();
        std::string fileContents = ss.str();

        std::string vertexShaderStr = "#version 450 core\n#define VertexShader\n" + fileContents;
        std::string fragmentShaderStr = "#version 450 core\n#define FragmentShader\n" + fileContents;
        shaderfile.close();

        const char* vertexShaderSrc = vertexShaderStr.c_str();
        const char* fragmentShaderSrc = fragmentShaderStr.c_str();

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
        glCompileShader(vertexShader);
        if(!checkCompileErrors(vertexShader, "VERTEX"))
        {
            glDeleteShader(vertexShader);
            m_ShaderID = 0; 
            return;
        }

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
        glCompileShader(fragmentShader);
        if(!checkCompileErrors(fragmentShader, "FRAGMENT"))
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            m_ShaderID = 0; 
            return;
        }

        m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertexShader);
        glAttachShader(m_ShaderID, fragmentShader);
        glLinkProgram(m_ShaderID);
        if(!checkLinkErrors(m_ShaderID))
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(m_ShaderID);
            m_ShaderID = 0;
            return;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        if(m_ShaderID != 0)
        glDeleteProgram(m_ShaderID);
    }

    void Shader::CalculateMartix(Camera& camera)
    {
                    // create transformations
            glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            glm::mat4 view          = camera.GetViewMatrix();
            glm::mat4 projection    = glm::mat4(1.0f);
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
            view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            projection = glm::perspective(glm::radians(45.0f), (float)StratConfig::WINDOW_HEIGHT / (float)StratConfig::WINDOW_WIDTH, 0.1f, 100.0f);
            // retrieve the matrix uniform locations
            unsigned int modelLoc = glGetUniformLocation(this->GetShader(), "model");
            unsigned int viewLoc  = glGetUniformLocation(this->GetShader(), "view");
            // pass them to the shaders (3 different ways)
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            this->setMat4("projection", projection);
    }

    bool Shader::checkCompileErrors(unsigned int shader, std::string type)
{       
        int success;
        char infoLog[512];

            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
                return false;
            }

        return true;
    }

    bool Shader::checkLinkErrors(unsigned int program)
    {
        int success;
        char infoLog[512];

            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
                return false;
            }
        return true;
    }
}


