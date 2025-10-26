#pragma once 

namespace StratEngine {

    struct Vertex;

    class VertexBuffer 
    {
        public:
            ~VertexBuffer() = default;

            virtual inline void Bind() { }; 
            virtual inline void Unbind() { };
            
            static std::unique_ptr<VertexBuffer> Create(std::vector<Vertex>& vertices);
    };
}