#pragma once
#include "Architecture/OpenGL/OpenGL_Buffer.h"
#include "Architecture/OpenGL/OpenGL_VArray.h"
#include "Renderer/Shader.h"

namespace StratEngine 
{
    struct Mesh 
    {
        std::string Name;
        std::vector<float> Vertices;
        size_t Size;
        OpenGL_VArray VAO;
        OpenGL_Buffer VBO;
        std::vector<ShaderAttributes> ShaderAttribs;
        Mesh(std::string name, std::vector<float>& vertices, std::vector<ShaderAttributes>& shaderAttributes, const char* texPath = "");
    };

    class TransformComponent 
    {
        public:
            TransformComponent();
            ~TransformComponent();

            void Move(glm::vec3 direction);
            inline glm::vec3 GetMoveDirection() { return m_MoveDirection; };
            inline void SetMoveDirection(glm::vec3 direction) { m_MoveDirection = direction; }; 

        private:
            glm::vec3 m_MoveDirection = {0.0f, 0.0f, 0.0f};
    };   

    class Model 
    {
        public:
            Model(std::string name);
            Model(std::string& name, std::unordered_map<std::string, Mesh> meshes);
            ~Model();

            void AddMesh(Mesh& mesh);
            void RemoveMesh(std::string& name);
            inline const std::string& GetName() { return m_Name; };
            inline const std::unordered_map<std::string, Mesh>& GetMeshes() const { return m_Meshes; };
            inline TransformComponent& GetTransformComponent() { return m_TransformComponent; };
        private:
            std::string m_Name;
            std::unordered_map<std::string, Mesh> m_Meshes;
            TransformComponent m_TransformComponent;
            glm::vec3 m_WorldPosition;

    };
}