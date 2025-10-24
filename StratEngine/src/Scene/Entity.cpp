#include "pchstrat.h"
#include "Entity.h"

namespace StratEngine
{
    Entity::Entity(entt::entity entity, Scene* scene)
    :  m_EntityID(entity), m_Scene(scene)
    {

    }

    Entity::~Entity()
    {

    }
}


