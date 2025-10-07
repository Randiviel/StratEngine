#pragma once

namespace StratEngine 
{
    class OpenGL_Buffer : public VertexBuffer 
    {
        public:
            OpenGL_Buffer(float* verticies, size_t size);
            ~OpenGL_Buffer();

            virtual inline void Bind() const override { glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID); }; 
            virtual inline void Unbind() const override { glBindBuffer(GL_ARRAY_BUFFER, 0); }; 
        private:
            unsigned int m_VertexBufferID;
    };
}