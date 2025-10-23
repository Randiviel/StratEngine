#pragma once

#include "entt/entt.hpp"

namespace StratEngine
{
    class Entity {
        public:
            Entity();
            ~Entity();
            inline std::string& GetName() { return m_Name; };

        private:
            std::string m_Name = "Entity";
    };

    class EntityManager
    {
        public:
            EntityManager();
            ~EntityManager();

        private:
        entt::registry m_Registry;
    };
}
