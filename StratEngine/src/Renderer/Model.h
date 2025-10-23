#pragma once
#include "Architecture/OpenGL/OpenGL_Buffer.h"
#include "Architecture/OpenGL/OpenGL_VArray.h"
#include "Renderer/Shader.h"
#include "Logger.h"

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
        GLuint Texture = 0;
        Mesh(std::string name, std::vector<float>& vertices, std::vector<ShaderAttributes>& shaderAttributes, const char* texPath = "");
    };

    class TransformComponent 
    {
        public:
            TransformComponent();
            ~TransformComponent();

            void Move(glm::vec3 direction);

            inline glm::vec3& GetPosition() { return m_Position; };
            inline void SetPosition(glm::vec3 direction) { m_Position = direction; }; 

            inline glm::vec3& GetScale() { return m_Scale; };
            inline void SetScale(float x, float y, float z) { m_Scale = glm::vec3(x, y, z); };

        private:
            glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
            glm::vec3 m_Scale = {1.0f, 1.0f, 1.0f};
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
            void SetTexture(const char* texPath);
            inline const char* GetTextureFilePath() { return m_FilePath; };
        private:
            std::string m_Name;
            std::unordered_map<std::string, Mesh> m_Meshes;
            TransformComponent m_TransformComponent;
            const char* m_FilePath = "";
            glm::vec3 m_WorldPosition;

    };
}