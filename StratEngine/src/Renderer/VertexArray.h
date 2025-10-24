#pragma once
#include "Shader.h"

namespace StratEngine {

    class VertexArray 
    {
        public:
            ~VertexArray() = default;

            virtual void Bind() const {};
            virtual void Unbind() const {}; 
    };
}