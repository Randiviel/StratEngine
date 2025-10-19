#pragma once
#include "Architecture/OpenGL/OpenGL_Buffer.h"
#include "Architecture/OpenGL/OpenGL_VArray.h"

namespace StratEngine 
{
    class OpenGL_Renderer : public Renderer
    {
        public:
            OpenGL_Renderer();
            ~OpenGL_Renderer();

            virtual void BeginScene(Camera& camera) override;
            virtual void EndScene() override;
            virtual void RenderModel(Model& model) override;
            virtual void SetShader(Shader& shader) override;
        private:
            Shader* m_Shader;

    };
}