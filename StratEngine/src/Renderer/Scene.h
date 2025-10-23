#pragma once
#include "Camera.h"
#include "Model.h"
#include "Renderer.h"
#include "Architecture/OpenGL/OpenGL_Renderer.h"

namespace StratEngine 
{
    class Scene 
    {
        public:
            Scene(std::string name);
            ~Scene();
            
            void AddModel(Model& model);
            void AddCamera(Camera& camera);
            void Render(Renderer& renderer);
            inline Camera& GetCamera() { return m_Camera; };
            inline std::string& GetName() { return m_Name; };
            inline std::unordered_map<std::string, Model>& GetAllModels() { return m_Models; };
        private:
            std::string m_Name;
            // TODO: Make Entitity Class and make it EntityContainer
            std::unordered_map<std::string, Model> m_Models;
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