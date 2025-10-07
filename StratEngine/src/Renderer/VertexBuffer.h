#pragma once 

namespace StratEngine {
    class VertexBuffer 
    {
        public:
            VertexBuffer() = default;
            ~VertexBuffer() = default;

            virtual inline void Bind() const { }; 
            virtual inline void Unbind() const { }; 
    };
}