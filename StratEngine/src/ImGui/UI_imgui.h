#pragma once

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <memory>
struct GLFWwindow;

namespace StratEngine {
    class UI_imgui {
    public:
        UI_imgui(std::unique_ptr<StratEngine::WinWindow>& window);
        ~UI_imgui();

        void Begin();
        void End();
        void ImGuiWindow();

        private:
        ImGuiIO m_io;
        GLFWwindow* m_WindowHandle;
        ImGuiViewport* m_mainViewport;
        ImGuiID m_dockingSpaceID;

        bool m_firstTime = true;

    };
}