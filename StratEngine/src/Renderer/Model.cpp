#include "pchstrat.h"
#include "Model.h"

namespace StratEngine
{
    Mesh::Mesh(std::string name, std::vector<float>& vertices, std::vector<ShaderAttributes>& shaderAttributes, const char* texPath) 
    : Name(name), Vertices(vertices), Size(vertices.size() * sizeof(float)), VAO(), VBO(vertices, Size), ShaderAttribs(shaderAttributes)
    {
        VAO.Bind();
        VBO.Bind();
        VAO.BindShaderAttrib(shaderAttributes);
        if(texPath && texPath[0] != '\0')
        {
            glGenTextures(1, &Texture);
            glBindTexture(GL_TEXTURE_2D, Texture);
            // set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // load and generate the texture
            int width, height, nrChannels;
            unsigned char *data = stbi_load(texPath, &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        VAO.Unbind();
        VBO.Unbind();
    }

    TransformComponent::TransformComponent()
    {

    }

    TransformComponent::~TransformComponent()
    {

    }

    void TransformComponent::Move(glm::vec3 direction)
    {
        m_Position = direction;
    }

    Model::Model(std::string name)
    {
        m_Name = name;
    }

    Model::Model(std::string& name, std::unordered_map<std::string, Mesh> meshes)
    {

    }

    Model::~Model()
    {
        
    }

    void Model::AddMesh(Mesh& mesh)
    {   
        m_Meshes.emplace(mesh.Name, std::move(mesh));
    }

    void Model::RemoveMesh(std::string &name)
    {
        m_Meshes.erase(name);
    }

    void Model::SetTexture(const char *texPath)
    {
        
    }
}


