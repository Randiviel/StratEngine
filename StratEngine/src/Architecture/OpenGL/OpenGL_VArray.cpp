#include "pchstrat.h"

namespace StratEngine
{
    OpenGL_VArray::OpenGL_VArray()
    {
        glGenVertexArrays(1, &m_VertexArrayID); 
    }

    OpenGL_VArray::~OpenGL_VArray()
    {
        glDeleteVertexArrays(1, &m_VertexArrayID);
    }

    void OpenGL_VArray::Bind() const
    {
        glBindVertexArray(m_VertexArrayID);
    }

    void OpenGL_VArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGL_VArray::AddBuffer(VertexBuffer& vertexBuffer)
    {
        this->Bind();
        vertexBuffer.Bind();
        int attribCount{0};
        int attribOffset{0};

        for(const auto i : m_ShaderAttributes)
        {
            unsigned int stride{0};
            for(const auto i : m_ShaderAttributes)
            {
                stride+= i.Count;
            }
            stride = stride * sizeof(float);
            glVertexAttribPointer(attribCount, i.Count, i.GetGLenumType(i.Type), i.Normalized, stride, reinterpret_cast<const void*>(attribOffset));
            glEnableVertexAttribArray(attribCount);
            attribCount++;
            attribOffset+=i.Count * sizeof(float);
        }

        glBindVertexArray(0); 
        glBindBuffer(GL_ARRAY_BUFFER, 0); 

    }

    void OpenGL_VArray::BindShaderAttrib(const std::vector<ShaderAttributes>& attributes)
    {
        m_ShaderAttributes = attributes;
    }
}
