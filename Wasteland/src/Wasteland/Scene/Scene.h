#pragma once

#include <entt/entt.hpp>

#include "Wasteland/Core/Timestep.h"

namespace Wasteland {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// TEMP
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};

}