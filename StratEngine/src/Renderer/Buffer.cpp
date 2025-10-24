#include "pchstrat.h"

namespace StratEngine
{
    VertexBuffer* VertexBuffer::Create(std::vector<Vertex>& vertices)
    {
        switch(GraphicsContext::GetAPI())
        {
            case GraphicsAPI::OpenGL:   return new OpenGL_Buffer(vertices); 
                                        break;
            case GraphicsAPI::None:     assert("GraphicsAPI = NONE, is not supported"); 
                                        return nullptr; 
                                        break;
        }
        
        return nullptr;
    }
}
