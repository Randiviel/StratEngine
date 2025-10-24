#pragma once

#include "Scene.h"

namespace StratEngine
{
    class Scene;

    class Entity {
        public:
            Entity(entt::entity entity, Scene* scene);
            ~Entity();

            template <typename T>
            T& GetComponent()
            {
                return m_Scene->GetRegistry().get<T>(m_EntityID);
            }

            template <typename T, typename... Args>
            T& AddComponent(Args&&... args)
            {
                return m_Scene->GetRegistry().emplace<T>(m_EntityID, std::forward<Args>(args)...);
            }

            template <typename T>
            void RemoveComponent()
            {
                m_Scene->GetRegistry().remove<T>(m_EntityID);
            }

        private:
            entt::entity m_EntityID;
            Scene* m_Scene;
    };
}
