#pragma once

namespace StratEngine {

    class Renderer {
        public:
            Renderer() = default;
            ~Renderer() = default;

            virtual void BeginScene() {};
            virtual void EndScene() {};

        private:

    };
}