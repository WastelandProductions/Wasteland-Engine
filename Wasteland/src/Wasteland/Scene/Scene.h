#pragma once

#include <entt/entt.hpp>

namespace Wasteland {

	class Scene
	{
	public:
		Scene();
		~Scene();
	private:
		entt::registry m_Registry;
	};

}