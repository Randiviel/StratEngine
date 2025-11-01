#pragma once
#include "Architecture/OpenGL/OpenGL_Buffer.h"
#include "Architecture/OpenGL/OpenGL_VArray.h"


namespace StratEngine 
{
    class Scene;
    struct MeshComponent;

    class OpenGL_Renderer : public Renderer
    {
        public:
            OpenGL_Renderer();
            ~OpenGL_Renderer();

            virtual void BeginScene(Camera& camera) override;
            virtual void EndScene() override;
            virtual void BindShader(std::shared_ptr<Shader> shader) override;
            virtual void DrawMesh(Entity& entity) override;
            virtual void DrawDebug(DrawMode mode, Entity& entity) override;
            inline virtual void Submit(Scene* scene) override { m_Scene = scene; };
            void InitFrameBuffer();
            inline virtual void* GetFrame() override { return (void*)(intptr_t)m_Texture; } ;
        private:
            std::shared_ptr<Shader> m_Shader;
            Scene* m_Scene;
            GLuint m_FBO = 0;
            GLuint m_Texture = 0;
            GLuint m_RBO = 0;
            GLuint m_DefaultTexture = 0;

    };
}