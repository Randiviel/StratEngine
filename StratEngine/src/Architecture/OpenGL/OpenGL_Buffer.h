#pragma once
#include "Renderer/VertexBuffer.h"

namespace StratEngine 
{
    class OpenGL_Buffer : public VertexBuffer 
    {
        public:
            OpenGL_Buffer(std::vector<float>& verticies, size_t size);
            ~OpenGL_Buffer();

            virtual void Bind() override; 
            virtual void Unbind() override; 
        private:
            unsigned int m_VertexBufferID;
            std::vector<float> m_Vertices;
            size_t m_Size;
    };
}