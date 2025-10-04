#pragma once 

namespace StratEngine {
    class VertexBuffer 
    {
        public:
            VertexBuffer(float* verticies, size_t size);
            ~VertexBuffer() = default;

            inline void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID); }; 
            inline void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }; 

        private:
            unsigned int m_VertexBufferID;
    };
}