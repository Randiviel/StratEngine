#pragma once
#include "Renderer/OpenGLBuffer.h"
#include "Shader.h"

namespace StratEngine {

    class VertexArray 
    {
        public:
            VertexArray();
            ~VertexArray();

            void Bind() const;
            void Unbind() const; 
            void AddBuffer(VertexBuffer& vertexBuffer);
            void BindShaderAttrib(const std::vector<ShaderAttributes>& attributes);

        private:
            unsigned int m_VertexArrayID;
            std::vector<ShaderAttributes> m_ShaderAttributes;
    };
}