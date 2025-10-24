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
        std::vector<Vertex> Vertcies;
        // I don't know for now -> uint32_t Texture = 0;
    };

    struct TagComponent
    {

    };

    struct RigidbodyComponent
    {

    };
}