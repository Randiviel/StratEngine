#include "pchstrat.h"

namespace StratEngine 
{
    OpenGL_Buffer::OpenGL_Buffer(std::vector<Vertex>& vertices)
    {
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    }

    OpenGL_Buffer::~OpenGL_Buffer()
    {
        glDeleteBuffers(1, &m_VertexBufferID);
    }

    void OpenGL_Buffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    }

    void OpenGL_Buffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
