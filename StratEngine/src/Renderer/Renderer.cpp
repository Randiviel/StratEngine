#include "pchstrat.h"

namespace StratEngine
{
    Renderer* Renderer::Create()
    {
        switch(GraphicsContext::GetAPI())
        {
            case GraphicsAPI::OpenGL:   return new OpenGL_Renderer(); 

            case GraphicsAPI::None:     assert("GraphicsAPI = NONE, is not supported"); 
                                        return nullptr; 
        }
        
        return nullptr;
    }
}
