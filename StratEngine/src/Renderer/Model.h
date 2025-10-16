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
        Mesh(std::string name, std::vector<float>& vertices, std::vector<ShaderAttributes>& shaderAttributes);
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
        private:
            std::string m_Name;
            std::unordered_map<std::string, Mesh> m_Meshes;
    };
}