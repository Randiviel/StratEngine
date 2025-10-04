#pragma once


namespace StratEngine
{
    class Shader
    {
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        Shader(const char* filepath);
        ~Shader();

        inline unsigned int GetShader() const { return m_ShaderID; }
    private:
        bool checkCompileErrors(unsigned int shader, std::string type);
        bool checkLinkErrors(unsigned int program);
    private:
        unsigned int m_ShaderID;

    };
}