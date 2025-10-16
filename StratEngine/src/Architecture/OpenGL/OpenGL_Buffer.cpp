#include "pchstrat.h"

namespace StratEngine 
{
    OpenGL_Buffer::OpenGL_Buffer(std::vector<float>& verticies, size_t size) : m_Vertices(verticies), m_Size(size) 
    {
        glGenBuffers(1, &m_VertexBufferID);
    }

    OpenGL_Buffer::~OpenGL_Buffer()
    {
        glDeleteBuffers(1, &m_VertexBufferID);
    }

    void OpenGL_Buffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, m_Size, m_Vertices.data(), GL_STATIC_DRAW);
    }

    void OpenGL_Buffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
