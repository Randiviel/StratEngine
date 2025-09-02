#pragma once

struct GLFWwindow;
#include "WinWindow/GlfwWindow.h"
#include <memory>
#include "ImGui/UI_imgui.h"

namespace StratEngine {

    class Application {
    public:
        Application();
        ~Application();

        void onEvent(Event& e);
        void Run();

        bool isRunning() const { return m_Running; }

        private:
        std::unique_ptr<WinWindow> m_WindowClass;
        std::unique_ptr<UI_imgui> m_ImGuiLayer;
        bool m_Running = true;

    };
}