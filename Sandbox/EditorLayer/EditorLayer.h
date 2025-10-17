#include "StratEngine.h"

class EditorLayer : public StratEngine::Layer {
    public:
        virtual void OnAttach() override
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
            ImGui_ImplOpenGL3_Init();
        }
        virtual void OnDetach() override
        {

        }
    private:
        virtual void OnUpdate(float deltaTime) override
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            if(m_ToolActive)
            {
                ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
                flags |= ImGuiWindowFlags_NoTitleBar;
                ImGui::Begin("My First Tool", &m_ToolActive, flags);
                ImGui::SetWindowPos(ImVec2(0, 0));
                if (ImGui::BeginMenuBar())
                {
                    if (ImGui::BeginMenu("File"))
                    {
                        if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                        if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
                        if (ImGui::MenuItem("Close", "Ctrl+W"))  { m_ToolActive = false; }
                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("Settings"))
                    {
                        if(ImGui::MenuItem("Properties")) { };
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenuBar();
                }

                // Generate samples and plot them
                float samples[100];
                for (int n = 0; n < 100; n++)
                    samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
                ImGui::PlotLines("Samples", samples, 100);

                // Display contents in a scrolling region
                ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
                ImGui::End();

                // ImGui::Begin("Shit", &m_ToolActive, flags);
                // ImGui::End();
            }
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        }

        virtual void OnEvent(StratEngine::Event& event) override
        {

        }

    public:
        inline void SetWindowHandle(GLFWwindow* windowhandle) { m_WindowHandle = windowhandle; };

    private:
        GLFWwindow* m_WindowHandle;
        bool m_ToolActive = true;
};