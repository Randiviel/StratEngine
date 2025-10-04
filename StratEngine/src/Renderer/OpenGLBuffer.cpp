#include "pchstrat.h"

namespace StratEngine 
{
    VertexBuffer::VertexBuffer(float* verticies, size_t size)
    {
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
    }
}

