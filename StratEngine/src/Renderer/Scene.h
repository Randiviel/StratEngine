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
            void AddRenderer(std::unique_ptr<OpenGL_Renderer> renderer);
            void Render();
            inline Camera& GetCamera() { return m_Camera; };
        private:
            std::string m_Name;
            // TODO: Make Entitity Class and make it EntityContainer
            std::unordered_map<std::string, Model> m_Models;
            Camera m_Camera;
            std::unique_ptr<OpenGL_Renderer> m_Renderer;
    };

    class SceneManager 
    {
        public:
            SceneManager();
            ~SceneManager();

            void AddScene(std::unique_ptr<Scene> scene);
        private:
            std::vector<std::unique_ptr> m_Scenes;
    }
}