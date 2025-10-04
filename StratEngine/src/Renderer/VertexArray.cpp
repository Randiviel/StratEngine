#include "pchstrat.h"

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        
        glEnableVertexAttribArray(0);

        glBindVertexArray(0); 
        glBindBuffer(GL_ARRAY_BUFFER, 0); 

    }
}
