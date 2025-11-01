#include "pchstrat.h"
#include "Scene.h"

namespace StratEngine {
    Scene::Scene(std::string name) :
    m_Name(name)
    {

    }

    Scene::~Scene()
    {

    }


    void Scene::AddCamera(Camera& camera)
    {
        m_Camera = camera;
    }

    void Scene::Render(Renderer& renderer)
    {
        
    }

    Entity Scene::CreateEntity(std::string name)
    {
        std::string newName = name;
        int counter = 1;
        
        while(m_Entities.contains(newName))
        {
            newName = name + std::to_string(counter);
            counter++;
        }
        auto entity = m_Registry.create();
        m_Entities.emplace(newName, Entity(entity, this, newName));
        return Entity(entity, this, newName);   
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
            // std::cout << "SceneManager has no scenes!" << '\n';
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
            // std::cout << "SceneManager has no scenes!" << '\n';
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
            // std::cout << "SceneManager has no scenes!" << '\n';
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
