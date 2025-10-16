#include "pchstrat.h"

namespace StratEngine {
    Scene::Scene(std::string name) :
    m_Name(name), m_Renderer(nullptr)
    {

    }

    Scene::~Scene()
    {

    }

    void Scene::AddModel(Model& model)
    {
        m_Models.emplace(model.GetName(), model);
    }

    void Scene::AddCamera(Camera& camera)
    {
        m_Camera = camera;
    }
    void Scene::AddRenderer(std::unique_ptr<OpenGL_Renderer> renderer)
    {
        m_Renderer = std::move(renderer);
    }
    void Scene::Render()
    {

        m_Renderer->BeginScene(m_Camera);
            for(const auto & [key, model] : m_Models)
            {            
                for(const auto & [name, mesh] : model.GetMeshes())
                {
                    m_Renderer->RenderMesh(mesh);
                }
            }       
        m_Renderer->EndScene();
    }
}
