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
            void SetShader(Shader& shader);
            void InitFrameBuffer();
            inline virtual void* GetFrame() override { return (void*)(intptr_t)m_Texture; } ;
            inline void SetEditorCamera(std::unique_ptr<Camera> camera) { m_EditorCamera = std::move(camera); };
        private:
            Shader* m_Shader;
            std::unique_ptr<Camera> m_EditorCamera = nullptr;
            GLuint m_FBO = 0;
            GLuint m_Texture = 0;
            GLuint m_RBO = 0;
            GLuint m_DefaultTexture = 0;

    };
}