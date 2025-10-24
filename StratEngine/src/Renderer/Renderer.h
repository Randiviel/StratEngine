#pragma once

namespace StratEngine {

    class Renderer {
        public:
            Renderer() = default;
            ~Renderer() = default;

            virtual void BeginScene(Camera& camera) {};
            virtual void EndScene() {};
            virtual void* GetFrame() = 0;
        private:

    };
}