#pragma once
#include "glm/glm.hpp"

namespace StratEngine 
{
    // struct TransformComponent
    // {

    // };

    struct Vertex
    {
        glm::vec4 Color = {0.0f, 0.0f, 0.0f, 1.0f};
        glm::vec3 Position = {0.0f, 0.0f, 0.0f};
        glm::vec2 TextureCoordinates = {0.0f, 0.0f};
    };

    struct MeshComponent
    {   
        std::string Name;
        std::vector<Vertex> Vertices;
        std::unique_ptr<VertexArray> VAO;
        std::unique_ptr<VertexBuffer> VBO;
        uint32_t Texture = 0;
        MeshComponent(std::vector<float>& vertices);
        void AddTexture(const char* filePath);
    };

    struct TagComponent
    {

    };

    struct RigidbodyComponent
    {

    };
}