#pragma once


namespace StratEngine 
{
    class OpenGL_Renderer : public Renderer
    {
        public:
            OpenGL_Renderer();
            ~OpenGL_Renderer();

            virtual void BeginScene() override;
            virtual void EndScene() override;
        private:
            Shader m_Shader;
            
    };
}