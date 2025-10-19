#pragma once

namespace StratEngine {

    class Renderer {
        public:
            Renderer() = default;
            ~Renderer() = default;

            virtual void BeginScene(Camera& camera) {};
            virtual void EndScene() {};
            virtual void RenderModel(Model& model) {};
            virtual void SetShader(Shader& shader) {};

        private:

    };
}