#pragma once

namespace StratEngine {

    class Shader;
    struct MeshComponent;
    class Entity;
    class Scene;

    enum class DrawMode
    {
        POINTS,
        TRIANGLES,
        LINES,
        LINES_STRIP,
        POLYGONS,
        QUADS,
    };

    class Renderer {
        public:
            Renderer() = default;
            ~Renderer() = default;

            virtual void BeginScene(Camera& camera) {};
            virtual void EndScene() {};
            virtual void* GetFrame() = 0;
            virtual void BindShader(std::shared_ptr<Shader> shader) {};
            virtual void DrawMesh(Entity& entity) {};
            virtual void DrawDebug(DrawMode mode, Entity& entity) {};
            inline virtual void Submit(Scene* scene) {};

            static Renderer* Create();
        private:

    };
}