#include "StratConfig.h"
#include "EditorLayer.h"
#include "glfw3.h"
#include "imgui/imgui_internal.h"

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
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\arial.ttf", 16.0f, NULL, 
                              io.Fonts->GetGlyphRangesDefault());
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_App->GetWindow()->GetWindowHandle(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
  
    // Dimensions
    style.TabRounding = 2.5f;
    style.TabBorderSize = 0.0f;
    style.FramePadding = ImVec2(6.0f, 1.0f);
}

void EditorLayer::OnDetach()
{

}

void EditorLayer::OnUpdate(float deltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    MainWindow();
    Viewport();
    EntityProperties();
    AssetManager();
    Objects(); 
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(m_App->GetWindow()->GetWindowHandle());     
}

void EditorLayer::OnEvent(StratEngine::Event &event)
{

}

void EditorLayer::MainWindow()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    
    ImGui::Begin("MainDockSpace", nullptr, window_flags);
    ImGui::PopStyleVar(3);
    
    // Menu Bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Create Scene", "Ctrl+S")) { 
                m_App->GetSceneManager()->CreateScene("Editor Scene"); 
            }
            if (ImGui::MenuItem("SetScene", "Ctrl+5")) { 
                m_App->GetSceneManager()->SetCurrentScene("Editor Scene"); 
            }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { m_ToolActive = false; }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Settings"))
        {
            if(ImGui::MenuItem("Properties")) { }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    
    // DockSpace
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_NoWindowMenuButton);
    
    ImGui::End();
}

void EditorLayer::Viewport()
{
    ImGuiWindowClass windowclass;
    windowclass.TabItemFlagsOverrideSet = ImGuiTabItemFlags_NoCloseButton;
    ImGui::SetNextWindowClass(&windowclass);
    
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Viewport", nullptr, flags);
    ImGui::PopStyleVar();   
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    ImGui::Image(m_App->GetRenderer().GetFrame(), viewportSize, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void EditorLayer::EntityProperties()
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Properties", nullptr, flags);
    ImGui::End();

}

void EditorLayer::SetupDockspace()
{

}

void EditorLayer::AssetManager()
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Assets", nullptr, flags);
    ImGui::End();
}

void EditorLayer::Objects()
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Objects", nullptr, flags);
    ImGui::End();
}
