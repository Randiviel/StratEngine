#include "pchstrat.h"
#include "Components.h"

namespace StratEngine
{
    MeshComponent::MeshComponent(std::vector<float>& vertices)
    {
        for(int i = 0; i < vertices.size(); i+= 5)
        {
            Vertex vertex;
            vertex.Position.x = vertices[i];
            vertex.Position.y = vertices[i+1];
            vertex.Position.z = vertices[i+2];
            vertex.TextureCoordinates.x = vertices[i+3];
            vertex.TextureCoordinates.y = vertices[i+4];
            Vertices.push_back(vertex);
        }

        std::vector<ShaderAttributes> layout = 
        {
        {"a_Color", ShaderAttribTypes::Float4, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float4), 4, false},
        {"a_Position", ShaderAttribTypes::Float3, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float3), 3, false},
        {"a_Texture", ShaderAttribTypes::Float2, ShaderAttributes::GetSizeOfType(ShaderAttribTypes::Float2), 2, false},
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
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
}

