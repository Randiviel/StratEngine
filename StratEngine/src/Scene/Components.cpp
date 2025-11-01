#include "pchstrat.h"
#include "Components.h"

namespace StratEngine
{
    MeshComponent::MeshComponent(const std::vector<float>& vertices)
    {
            for(int i = 0; i < vertices.size(); i+= 8)
            {
                Vertex vertex;
                vertex.Position.x = vertices[i];
                vertex.Position.y = vertices[i+1];
                vertex.Position.z = vertices[i+2];
                vertex.Normal.x = vertices[i+3];
                vertex.Normal.y = vertices[i+4];
                vertex.Normal.z = vertices[i+5];
                vertex.TextureCoordinates.x = vertices[i+6];
                vertex.TextureCoordinates.y = vertices[i+7];
                Vertices.push_back(vertex);
            }

        std::vector<ShaderAttributes> layout = 
        {
        {"a_Position", ShaderAttribTypes::Float3, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float3), 3, false},
        {"a_Normal", ShaderAttribTypes::Float3, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float3), 3, false},
        {"a_Texture", ShaderAttribTypes::Float2, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float2), 2, false},
        {"a_Color", ShaderAttribTypes::Float4, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float4), 4, false}
        };

        VAO = VertexArray::Create(); 
        VBO = VertexBuffer::Create(Vertices);

        VAO->Bind();
        VBO->Bind();

        VAO->SetVertexLayout(layout);

        VAO->Unbind();
        VBO->Unbind();
    }

    void MeshComponent::AddTexture(const char* filePath)
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
        unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
        if (data)
        {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    glm::mat4 TransformComponent::GetModelMatrix()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, Position);
        model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, Scale);
        return model;
    }
}
