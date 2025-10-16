#include "pchstrat.h"

namespace StratEngine
{
    Mesh::Mesh(std::string name, std::vector<float>& vertices, std::vector<ShaderAttributes>& shaderAttributes) 
    : Name(name), Vertices(vertices), Size(vertices.size() * sizeof(float)), VAO(), VBO(vertices, Size), ShaderAttribs(shaderAttributes)
    {
        VAO.Bind();
        VBO.Bind();
        VAO.BindShaderAttrib(shaderAttributes);
        VAO.Unbind();
        VBO.Unbind();
    }

    Model::Model(std::string name)
    {

    }

    Model::Model(std::string& name, std::unordered_map<std::string, Mesh> meshes)
    {

    }

    Model::~Model()
    {
        
    }

    void Model::AddMesh(Mesh& mesh)
    {
        m_Meshes.emplace(mesh.Name, mesh);
    }

    void Model::RemoveMesh(std::string &name)
    {
        m_Meshes.erase(name);
    }

}
