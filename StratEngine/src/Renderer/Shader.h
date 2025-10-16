#pragma once
#include "glad/glad.h"

namespace StratEngine
{
    enum class ShaderAttribTypes
    {
        None,
        Float,
        Float2,
        Float3,
        Float4,
        Mat2,
        Mat3,
    };

    struct ShaderAttributes
    {
        std::string Name;
        ShaderAttribTypes Type;
        unsigned int Size;
        unsigned int Count;
        bool Normalized;

        static unsigned int GetSizeOfType(ShaderAttribTypes type)
        {
            switch(type)
            {
                case ShaderAttribTypes::None:     return 0;
                case ShaderAttribTypes::Float:    return 4;
                case ShaderAttribTypes::Float2:   return 4 * 2;
                case ShaderAttribTypes::Float3:   return 4 * 3;
                case ShaderAttribTypes::Float4:   return 4 * 4;
                case ShaderAttribTypes::Mat2:     return 4 * 2 * 2;
                case ShaderAttribTypes::Mat3:     return 4 * 3 * 3;
            }
            return 0;
        }

        static GLenum GetGLenumType(ShaderAttribTypes type)
        {
            switch(type)
            {
                case ShaderAttribTypes::None:     return 0;
                case ShaderAttribTypes::Float:    return GL_FLOAT;
                case ShaderAttribTypes::Float2:   return GL_FLOAT;
                case ShaderAttribTypes::Float3:   return GL_FLOAT;
                case ShaderAttribTypes::Float4:   return GL_FLOAT;
                case ShaderAttribTypes::Mat2:     return 0;
                case ShaderAttribTypes::Mat3:     return 0;
            }
            return 0;
        }
    };

    class Shader
    {
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        Shader(const char* filepath);
        ~Shader();

        inline unsigned int GetShader() const { return m_ShaderID; }

        void setBool(const std::string &name, bool value) const
        {         
            glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), (int)value); 
        }
        // ------------------------------------------------------------------------
        void setInt(const std::string &name, int value) const
        { 
            glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value); 
        }
        // ------------------------------------------------------------------------
        void setFloat(const std::string &name, float value) const
        { 
            glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value); 
        }
        // ------------------------------------------------------------------------
        void setVec2(const std::string &name, const glm::vec2 &value) const
        { 
            glUniform2fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &value[0]); 
        }
        void setVec2(const std::string &name, float x, float y) const
        { 
            glUniform2f(glGetUniformLocation(m_ShaderID, name.c_str()), x, y); 
        }
        // ------------------------------------------------------------------------
        void setVec3(const std::string &name, const glm::vec3 &value) const
        { 
            glUniform3fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &value[0]); 
        }
        void setVec3(const std::string &name, float x, float y, float z) const
        { 
            glUniform3f(glGetUniformLocation(m_ShaderID, name.c_str()), x, y, z); 
        }
        // ------------------------------------------------------------------------
        void setVec4(const std::string &name, const glm::vec4 &value) const
        { 
            glUniform4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &value[0]); 
        }
        void setVec4(const std::string &name, float x, float y, float z, float w) const
        { 
            glUniform4f(glGetUniformLocation(m_ShaderID, name.c_str()), x, y, z, w); 
        }
        // ------------------------------------------------------------------------
        void setMat2(const std::string &name, const glm::mat2 &mat) const
        {
            glUniformMatrix2fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void setMat3(const std::string &name, const glm::mat3 &mat) const
        {
            glUniformMatrix3fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void setMat4(const std::string &name, const glm::mat4 &mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void CalculateMartix(Camera& camera);
    private:
        bool checkCompileErrors(unsigned int shader, std::string type);
        bool checkLinkErrors(unsigned int program);
    private:
        unsigned int m_ShaderID;

    };
}