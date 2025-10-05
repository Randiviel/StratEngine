#include "pchstrat.h"
#include "VertexArray.h"

namespace StratEngine
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_VertexArrayID); 
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_VertexArrayID);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_VertexArrayID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddBuffer(VertexBuffer& vertexBuffer)
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

    void VertexArray::BindShaderAttrib(const std::vector<ShaderAttributes>& attributes)
    {
        m_ShaderAttributes = attributes;
    }
}

