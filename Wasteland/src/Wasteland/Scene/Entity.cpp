#include "wlpch.h"
#include "Entity.h"

namespace Wasteland {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{

	}

}