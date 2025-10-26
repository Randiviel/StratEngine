#include "pchstrat.h"

namespace StratEngine
{
    std::unique_ptr<VertexArray> VertexArray::Create()
    {
        switch(GraphicsContext::GetAPI())
        {
            case GraphicsAPI::OpenGL:   return std::make_unique<OpenGL_VArray>();
            
            case GraphicsAPI::None:     assert("GraphicsAPI = NONE, is not supported"); 
                                        return nullptr;
        }
        
        return nullptr;
    }
}
