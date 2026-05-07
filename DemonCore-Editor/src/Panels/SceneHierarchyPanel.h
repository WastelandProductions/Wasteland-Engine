#pragma once

#include "Wasteland/Core/Core.h"
#include "Wasteland/Core/Log.h"
#include "Wasteland/Scene/Scene.h"
#include "Wasteland/Scene/Entity.h"

namespace Wasteland {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}