#include "EditorLayer.h"
#include "StratConfig.h"
#include "glfw3.h"
#include "imgui/imgui_internal.h"
#include "EditorImporter.h"
#include "Vendor/Include/portable-file-dialogs.h"

EditorLayer::EditorLayer(StratEngine::Application* app)
: m_Engine(app)
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
    ImGui_ImplGlfw_InitForOpenGL(m_Engine->GetWindow().GetWindowHandle(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
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

    std::shared_ptr<StratEngine::Shader> myShader = std::make_shared<StratEngine::Shader>("Shaders/SandBoxShader.glsl");
    m_Engine->GetRenderer().BindShader(myShader);

        std::vector<float> vertices = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f
        };

        m_Engine->GetSceneManager().CreateScene("myScene");
        m_Engine->GetSceneManager().SetCurrentScene("myScene");
        auto* myScene = m_Engine->GetSceneManager().GetCurrentScene();
        auto& myEntity = myScene->CreateEntity("Cube")
                    .AddComponent<StratEngine::MeshComponent>(vertices)
                    .AddComponent<StratEngine::TransformComponent>(glm::vec3(5.0f, 0.0f, 0.0f));

        Editor::Importer::ImportObject(myScene, "Assets/Container.FBX");
        
        auto& light = myScene->CreateEntity("Light")
                    .AddComponent<StratEngine::MeshComponent>(vertices)
                    .AddComponent<StratEngine::TransformComponent>()
                    .AddComponent<StratEngine::LightComponent>();

        m_Engine->GetRenderer().Submit(myScene);

}

void EditorLayer::OnDetach()
{

}

void EditorLayer::OnUpdate(float deltaTime)
{
    static bool onlyOnce = true;
    CameraInput(deltaTime);
    auto* currentScene = m_Engine->GetSceneManager().GetCurrentScene();
    auto& renderer = m_Engine->GetRenderer();
    auto view = currentScene->GetRegistry().view<StratEngine::MeshComponent>();

    renderer.BeginScene(m_EditorCamera);

        for(auto& entity : view)
        {
            StratEngine::Entity tempEntity(entity, currentScene);
            renderer.DrawMesh(tempEntity);
        }

    renderer.EndScene();

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
    glfwMakeContextCurrent(m_Engine->GetWindow().GetWindowHandle());    
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
            if (ImGui::MenuItem("Create Scene", "Ctrl+S"))
            { 
                m_Engine->GetSceneManager().CreateScene("Editor Scene"); 
            }
            if (ImGui::MenuItem("Import Asset", "Ctrl+5")) 
            {
                auto selection = pfd::open_file("Select a file", ".",
                                    { "All Files", "*" },
                                    pfd::opt::none).result();

                if(!selection.empty())
                {   
                    STRAT_CLIENT_INFO("{0}", selection[0].c_str());
                    Editor::Importer::ImportObject(m_Engine->GetSceneManager().GetCurrentScene(), selection[0].c_str());
                }
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
    ImGui::Image(m_Engine->GetRenderer().GetFrame(), viewportSize, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void EditorLayer::EntityProperties()
{
    auto* currentScene = m_Engine->GetSceneManager().GetCurrentScene();
    auto it = currentScene->GetEntities().find(m_EditorInfo.SelectedEntity);
    if(it == currentScene->GetEntities().end()) return;

    auto& transform = it->second.GetComponent<StratEngine::TransformComponent>();

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Properties", nullptr, flags);

        // Wklęsły panel z ramką
        ImGui::BeginChild("PropertiesPanel", ImVec2(0, 105), true, 
                        ImGuiWindowFlags_AlwaysUseWindowPadding);
        
        // Tutaj umieszczasz zawartość (inputy, slidery, itp.)

        ImGui::Text("Transform");
        ImGui::Separator();
        
        ImGui::DragFloat3("Position", &transform.Position.x, 0.1f);
        ImGui::DragFloat3("Rotation", &transform.Rotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &transform.Scale.x, 0.1f);
        
        ImGui::EndChild();

        ImGui::BeginChild("Texture", ImVec2(0, 100), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
        ImGui::Text("Texture");
        ImGui::Separator();
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
        if(ImGui::Button("Select file", ImVec2(75.0f, 50.0f)))
        {

            auto selection = pfd::open_file("Select a file", ".",
                                { "Image Files", "*.png *.jpg *.jpeg *.bmp" },
                                    pfd::opt::none).result();

            if(!selection.empty())
            {   
                STRAT_CLIENT_INFO("{0}", selection[0].c_str());
                auto& mesh = it->second.GetComponent<StratEngine::MeshComponent>();
                mesh.AddTexture(selection[0].c_str());
            }
        }
        ImGui::PopStyleVar(1);
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
    auto* currentScene = m_Engine->GetSceneManager().GetCurrentScene();
    static int selectedRow = -1;
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Objects", nullptr, flags);
    // Lewa strona - lista obiektów
    ImGui::BeginChild("ObjectList", ImVec2(200, 0), true);
    {
        if(ImGui::BeginTable("MyTable", 1, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            int row = 0;
            for(auto& [name, entity] : currentScene->GetEntities())
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                
                if(ImGui::Selectable(name.c_str(), selectedRow == row, 
                                    ImGuiSelectableFlags_SpanAllColumns))
                {
                    selectedRow = row;
                    m_EditorInfo.SelectedEntity = name; // Zapisz nazwę wybranego modelu
                }
                row++;
            }
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

void EditorLayer::CameraInput(float deltatime)
{
    if(m_Engine->IsMouseLocked())
    {
        if(StratEngine::Input::IsKeyPressed(STRAT_KEY_W))
                m_EditorCamera.MoveCamera(StratEngine::CameraMovement::FORWARD, deltatime);
        if(StratEngine::Input::IsKeyPressed(STRAT_KEY_S))
                m_EditorCamera.MoveCamera(StratEngine::CameraMovement::BACKWARD, deltatime);
        if(StratEngine::Input::IsKeyPressed(STRAT_KEY_A))
                m_EditorCamera.MoveCamera(StratEngine::CameraMovement::LEFT, deltatime);
        if(StratEngine::Input::IsKeyPressed(STRAT_KEY_D))
                m_EditorCamera.MoveCamera(StratEngine::CameraMovement::RIGHT, deltatime);

        auto mousePos = StratEngine::Input::GetMousePosition();
        m_EditorCamera.ProcessMouseMovement(mousePos.first, mousePos.second);
    }
    else
    {
        m_EditorCamera.ResetFirstTime();
    }

}
