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
            virtual void RenderMesh(const Mesh& mesh) override;
            void SetShader(Shader& shader);
        private:
            Shader* m_Shader;

    };
}