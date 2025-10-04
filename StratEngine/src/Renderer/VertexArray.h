#pragma once
#include "Renderer/OpenGLBuffer.h"

namespace StratEngine {

    class VertexArray 
    {
        public:
            VertexArray();
            ~VertexArray();

            void Bind() const;
            void Unbind() const; 
            void AddBuffer(VertexBuffer& vertexBuffer);

        private:
            unsigned int m_VertexArrayID;
    };
}