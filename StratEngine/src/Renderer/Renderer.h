#pragma once

namespace StratEngine {

    class Shader;
    struct MeshComponent;

    class Renderer {
        public:
            Renderer() = default;
            ~Renderer() = default;

            virtual void BeginScene(Camera& camera) {};
            virtual void EndScene() {};
            virtual void* GetFrame() = 0;
            virtual void BindShader(std::shared_ptr<Shader> shader) {};
            virtual void DrawMesh(MeshComponent& mesh) {};

            static Renderer* Create();
        private:

    };
}