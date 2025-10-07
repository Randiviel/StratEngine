#pragma once
#include "Shader.h"

namespace StratEngine {

    class VertexArray 
    {
        public:
            VertexArray() = default;
            ~VertexArray() = default;

            virtual void Bind() const {};
            virtual void Unbind() const {}; 
            virtual void AddBuffer(VertexBuffer& vertexBuffer) {};
            virtual void BindShaderAttrib(const std::vector<ShaderAttributes>& attributes) {};
    };
}