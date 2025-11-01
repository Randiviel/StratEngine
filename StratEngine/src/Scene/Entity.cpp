#include "pchstrat.h"
#include "Entity.h"

namespace StratEngine
{
    Entity::Entity(entt::entity entity, Scene* scene, std::string name)
    :  m_EntityID(entity), m_Scene(scene), m_Name(name)
    {

    }

    Entity::~Entity()
    {

    }
}


