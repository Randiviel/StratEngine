#pragma once
#include "glm/glm.hpp"

namespace StratEngine 
{
    struct TransformComponent
    {
        glm::vec3 Position = {0.0f, 0.0f, 0.0f};
        glm::vec3 Rotation = {0.0f, 0.0f, 0.0f};
        glm::vec3 Scale = {1.0f, 1.0f, 1.0f};

        glm::mat4 GetModelMatrix();
    };

    struct Vertex
    {
        glm::vec3 Position = {0.0f, 0.0f, 0.0f};
        glm::vec3 Normal = {0.0f, 0.0f, 0.0f};
        glm::vec2 TextureCoordinates = {0.0f, 0.0f};
        glm::vec4 Color = {0.0f, 0.0f, 0.0f, 1.0f};
    };

    struct MeshComponent
    {   
        std::vector<Vertex> Vertices;
        std::unique_ptr<VertexArray> VAO;
        std::unique_ptr<VertexBuffer> VBO;
        uint32_t Texture = 0;
        MeshComponent(const std::vector<float>& vertices);
        void AddTexture(const char* filePath);
    };

    struct TagComponent
    {
        std::string Name;
    };

    struct RigidbodyComponent
    {

    };

    struct CollisionComponent
    {
        
    };

    struct MaterialComponent
    {
        
    };

    struct LightComponent
    {
        glm::vec3 Color = {1.0f, 0.5f, 0.5f};
    };
}