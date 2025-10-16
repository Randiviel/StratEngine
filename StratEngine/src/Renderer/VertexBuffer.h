#pragma once 

namespace StratEngine {
    class VertexBuffer 
    {
        public:
            VertexBuffer() = default;
            ~VertexBuffer() = default;

            virtual inline void Bind() { }; 
            virtual inline void Unbind() { }; 
    };
}