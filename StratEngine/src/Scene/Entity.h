#pragma once

#include "Scene.h"

namespace StratEngine
{
    class Scene;

    class Entity {
        public:
            Entity(entt::entity entity, Scene* scene, std::string name = "Default");
            ~Entity();

            template <typename T>
            T& GetComponent()
            {
                return m_Scene->GetRegistry().get<T>(m_EntityID);
            }

            template <typename T, typename... Args>
            Entity& AddComponent(Args&&... args)
            {   
                m_Scene->GetRegistry().emplace<T>(m_EntityID, std::forward<Args>(args)...);
                return *this;
            }

            template <typename T>
            void RemoveComponent()
            {
                m_Scene->GetRegistry().remove<T>(m_EntityID);
            }

            inline entt::entity GetID() const { return m_EntityID; };

            inline std::string& GetName() { return m_Name; };

            template <typename T>
            bool HasComponent()
            {
                return m_Scene->GetRegistry().all_of<T>(m_EntityID);
            }

        private:
            std::string m_Name;
            entt::entity m_EntityID;
            Scene* m_Scene;
    };
}
