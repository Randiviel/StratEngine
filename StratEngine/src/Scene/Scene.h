#pragma once
#include "Renderer/Camera.h"
#include "Renderer/Renderer.h"
#include "Architecture/OpenGL/OpenGL_Renderer.h"
#include "entt/entt.hpp"

namespace StratEngine 
{
    class Entity;

    class Scene 
    {
        public:
            Scene(std::string name);
            ~Scene();
            void AddCamera(Camera& camera);
            void Render(Renderer& renderer);
            
            inline Camera& GetCamera() { return m_Camera; };
            inline std::string& GetName() { return m_Name; };
            inline entt::registry& GetRegistry() { return m_Registry; };
            Entity CreateEntity();
        private:
            std::string m_Name;
            entt::registry m_Registry;
            Camera m_Camera;
    };

    class SceneManager 
    {
        public:
            SceneManager();
            ~SceneManager();

            void DeleteScene(std::string& sceneName);
            void SetCurrentScene(const std::string& sceneName);
            Scene& CreateScene(std::string name);
            Scene* GetCurrentScene();
            inline std::unordered_map<std::string, std::unique_ptr<Scene>>& GetAllScenes() { return m_Scenes; };
        private:
            std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
            std::string m_CurrentScene;
            
    };
}