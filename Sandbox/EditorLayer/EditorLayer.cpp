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
    NewFrame();
    
    MainWindow();
    Viewport();
    EntityProperties();
    AssetManager();
    Objects(); 
    
    EndFrame();
}

void EditorLayer::OnEvent()
{
    if(StratEngine::Input::IsKeyPressed(STRAT_KEY_J))
    {
        STRAT_CLIENT_TRACE("The key J is pressed!");
    }
}

void EditorLayer::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void EditorLayer::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(m_App->GetWindow()->GetWindowHandle());    
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
            if (ImGui::MenuItem("Close", "Ctrl+W")) { m_EditorInfo.ToolActive = false; }
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
    float position[3] = {0.0f, 0.0f, 0.0f};
    float scale[3] = {1.0f, 1.0f, 1.0f};
    auto currentScene = m_App->GetSceneManager()->GetCurrentScene();

        // if(currentScene != nullptr)
        // {
        //     auto& models = currentScene->GetAllModels();
        //     auto it = models.find(m_EditorInfo.SelectedEntity);
        //     if(it != models.end())
        //     {
        //         auto& modelPos = it->second.GetTransformComponent().GetPosition();
        //         auto& modelScale = it->second.GetTransformComponent().GetScale();
        //         position[0] = modelPos.x;
        //         position[1] = modelPos.y;
        //         position[2] = modelPos.z;
        //         scale[0] = modelScale.x;
        //         scale[1] = modelScale.y;
        //         scale[2] = modelScale.z;

        //     }
        // }

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Properties", nullptr, flags);

            // Wklęsły panel z ramką
        ImGui::BeginChild("PropertiesPanel", ImVec2(0, 105), true, 
                        ImGuiWindowFlags_AlwaysUseWindowPadding);
        
        // Tutaj umieszczasz zawartość (inputy, slidery, itp.)
        ImGui::Text("Transform");
        ImGui::Separator();
        
        ImGui::DragFloat3("Position", position, 0.1f);
        
        float rotation[3] = {0.0f, 0.0f, 0.0f};
        ImGui::DragFloat3("Rotation", rotation, 0.1f);
        ImGui::DragFloat3("Scale", scale, 0.1f);

        // if(it != models.end())
        // {
        //     it->second.GetTransformComponent().SetPosition(glm::vec3(position[0], position[1], position[2]));
        //     it->second.GetTransformComponent().SetScale(scale[0], scale[1], scale[2]);
        // }
        
        ImGui::EndChild();

        ImGui::BeginChild("Texture", ImVec2(0, 100), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
        ImGui::Text("Texture");
        ImGui::Separator();
        ImGui::EndChild();

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
    static int selectedRow = -1;
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Objects", nullptr, flags);
    // Lewa strona - lista obiektów
    ImGui::BeginChild("ObjectList", ImVec2(200, 0), true);
    {
        if(ImGui::BeginTable("MyTable", 1, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            // int row = 0;
            // for(auto& model : m_App->GetSceneManager()->GetCurrentScene()->GetAllModels())
            // {
            //     ImGui::TableNextRow();
            //     ImGui::TableSetColumnIndex(0);
                
            //     if(ImGui::Selectable(model.first.c_str(), selectedRow == row, 
            //                         ImGuiSelectableFlags_SpanAllColumns))
            //     {
            //         selectedRow = row;
            //         m_EditorInfo.SelectedEntity = model.first; // Zapisz nazwę wybranego modelu
            //     }
            //     row++;
            // }
            ImGui::EndTable();
        }
    }
    ImGui::EndChild();
    
    // ImGui::SameLine(); // To samo okno, obok
    
    // // Prawa strona - szczegóły wybranego obiektu
    // ImGui::BeginChild("ObjectDetails", ImVec2(0, 0), true);
    // {
    //     if(selectedRow >= 0)
    //     {
    //         ImGui::Text("Selected: %s", m_EditorInfo.SelectedEntity.c_str());
    //         ImGui::Separator();
            
    //         // Tutaj możesz dodać właściwości wybranego obiektu
    //         auto& models = m_App->GetSceneManager()->GetCurrentScene()->GetAllModels();
    //         auto it = models.find(m_EditorInfo.SelectedEntity);
    //         if(it != models.end())
    //         {
    //             // Edytuj właściwości modelu
    //             ImGui::Text("Position: guwno");
    //             // ImGui::DragFloat3("Pos", &it->second->position);
                
    //             ImGui::Text("Rotation: guwno");
    //             // ImGui::DragFloat3("Rot", &it->second->rotation);
    //         }
    //     }
    //     else
    //     {
    //         ImGui::TextDisabled("No object selected");
    //     }
    // }
    // ImGui::EndChild();

    ImGui::End();
}
