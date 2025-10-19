#include "StratConfig.h"
#include "EditorLayer.h"

EditorLayer::EditorLayer(StratEngine::Application* app)
: m_App(app)
{

}

void EditorLayer::OnAttach()
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

void EditorLayer::OnDetach()
{

}

void EditorLayer::OnUpdate(float deltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
        if(m_FirstLaunch)
        {
            ImGui::SetNextWindowSize(ImVec2(250, StratConfig::WINDOW_WIDTH));
            m_FirstLaunch = false;
        };

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
                        if (ImGui::MenuItem("Create Scene", "Ctrl+S"))   { m_App->GetSceneManager()->CreateScene("Editor Scene"); };
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

            // Display contents in a scrolling region
            ImGui::TextColored(ImVec4(1,1,0,1), "All Scenes:");
            ImGui::BeginChild("Scrolling");
            int i = 0;
            for(auto& [key, scene] : m_App->GetSceneManager()->GetAllScenes())
            {
                ImGui::Text(scene->GetName().c_str(), i);
                i++;
            };
                
            ImGui::EndChild();
            ImGui::End();
        }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
}

void EditorLayer::OnEvent(StratEngine::Event &event)
{

}
