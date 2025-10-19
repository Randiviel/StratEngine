#include "pchstrat.h"

namespace StratEngine {
    Scene::Scene(std::string name) :
    m_Name(name)
    {

    }

    Scene::~Scene()
    {

    }

    void Scene::AddModel(Model& model)
    {
        m_Models.insert({model.GetName(), model});
    }

    void Scene::AddCamera(Camera& camera)
    {
        m_Camera = camera;
    }

    void Scene::Render(Renderer& renderer)
    {
        if(m_Models.empty())
        {
            renderer.BeginScene(m_Camera);
            renderer.EndScene();
        }
        else
        {
            renderer.BeginScene(m_Camera);
                for(auto & [key, model] : m_Models)
                {               
                    renderer.RenderModel(model);
                }       
            renderer.EndScene();
        }

    }

    SceneManager::SceneManager()
    {

    }

    SceneManager::~SceneManager()
    {

    }

    void SceneManager::DeleteScene(std::string& sceneName)
    {
        if(m_Scenes.empty())
        {
            std::cout << "SceneManager has no scenes!" << '\n';
            return;
        }

        if(auto scene = m_Scenes.find(sceneName); scene != m_Scenes.end())
            m_Scenes.erase(sceneName);
        else
            std::cout << "Scene '" << sceneName << "' not found!" << '\n';

    }

    void SceneManager::SetCurrentScene(const std::string& sceneName)
    {
        if(m_Scenes.empty())
        {
            std::cout << "SceneManager has no scenes!" << '\n';
            return;
        }

        if(auto scene = m_Scenes.find(sceneName); scene != m_Scenes.end())
            m_CurrentScene = sceneName;
        else
            std::cout << "Couldn't find the scene!";
    }

    Scene& SceneManager::CreateScene(std::string name)
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(name);
        m_Scenes.emplace(scene->GetName(), std::move(scene));
        return *m_Scenes[name];
    }

    Scene* SceneManager::GetCurrentScene()
    {
        if(m_Scenes.empty())
        {
            std::cout << "SceneManager has no scenes!" << '\n';
            return nullptr;
        }

        auto it = m_Scenes.find(m_CurrentScene);
        if(it != m_Scenes.end())
        {
            return it->second.get();
        }

        return nullptr;
    }
}
