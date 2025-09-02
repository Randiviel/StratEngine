#include "pchstrat.h"

namespace StratEngine {

    UI_imgui::UI_imgui(std::unique_ptr<StratEngine::WinWindow>& window) {
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_io = ImGui::GetIO();
        m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
        m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      
        m_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         
        m_WindowHandle = window->GetWindowHandle();
        
        ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true);          
        ImGui_ImplOpenGL3_Init();

    }

        UI_imgui::~UI_imgui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UI_imgui::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuiWindow();
    }

    void UI_imgui::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    void UI_imgui::ImGuiWindow()
    {
        m_mainViewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(m_mainViewport->Pos);
        ImGui::SetNextWindowSize(m_mainViewport->Size);
        ImGui::SetNextWindowViewport(m_mainViewport->ID);
        

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | 
                                    ImGuiWindowFlags_NoDocking |
                                    ImGuiWindowFlags_NoTitleBar | 
                                    ImGuiWindowFlags_NoCollapse | 
                                    ImGuiWindowFlags_NoResize | 
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoBringToFrontOnFocus | 
                                    ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        
        if(ImGui::Begin("StratEngine", nullptr, window_flags))
        {
            ImGui::PopStyleVar(3);
            
            
            if(ImGui::BeginMenuBar())
            {
                if(ImGui::BeginMenu("File"))
                {
                    if(ImGui::MenuItem("Save", "Ctrl+S"));
                    if(ImGui::MenuItem("Exit"));
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            

            m_dockingSpaceID = ImGui::GetID("MyDockSpace");
            // if (m_firstTime)
            // {
            //     m_firstTime = false;
                
            //     ImGui::DockBuilderRemoveNode(m_dockingSpaceID);
            //     ImGui::DockBuilderAddNode(m_dockingSpaceID, ImGuiDockNodeFlags_DockSpace);
            //     ImGui::DockBuilderSetNodeSize(m_dockingSpaceID, m_mainViewport->Size);
                
            //     
            //     m_dockLeftID = ImGui::DockBuilderSplitNode(m_dockingSpaceID, ImGuiDir_Left, 0.25f, nullptr, &m_dockingSpaceID);
            //     m_dockDownID = ImGui::DockBuilderSplitNode(m_dockingSpaceID, ImGuiDir_Down, 0.3f, nullptr, &m_dockingSpaceID);

            //     ImGui::DockBuilderFinish(m_dockingSpaceID);
            // }
            
            // ImGui::DockSpace(m_dockingSpaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        }
        else
        {
            ImGui::PopStyleVar(3);
        }
        
        ImGui::End();

        if (ImGui::Begin("Console"))
        {
            ImGui::Text("Debug console");
            ImGui::TextWrapped("Log messages here...");
        }
        ImGui::End();
    }
    
}