#pragma once

namespace StratEngine
{
    enum class GraphicsAPI
    {
        None = 0,
        OpenGL = 1
    };

    class GraphicsContext
    {
        public:
            static inline GraphicsAPI GetAPI() { return m_GraphicsContext; };
        private:
            static GraphicsAPI m_GraphicsContext;

    };
}