#pragma once

namespace StratEngine 
{
    struct Mesh 
    {
        std::string name;
        std::unique_ptr<float[]> vertices;
        size_t size;
    };

    class Model 
    {
        public:
            Model(std::string& name);
            Model(std::string& name, std::unordered_map<std::string, Mesh> meshes);
            ~Model();

            void AddMesh(Mesh& mesh);
            void RemoveMesh(std::string& name);
        private:
            std::string m_Name;
            std::unordered_map<std::string, Mesh> m_Meshes;
    };
}