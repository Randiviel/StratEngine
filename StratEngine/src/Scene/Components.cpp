#include "pchstrat.h"

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
}
