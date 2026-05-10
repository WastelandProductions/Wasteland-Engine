#pragma once

#include "Wasteland.h"
#include "Panels/SceneHierarchyPanel.h"
#include <Wasteland/Renderer/Texture.h>

#include "Wasteland/Renderer/EditorCamera.h"

namespace Wasteland {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		OrthographicCameraController m_CameraController;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;

		Ref<Texture2D> m_CheckerboardTexture;
		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		int m_GizmoType = -1;

		uint32_t m_MapWidth, m_MapHeight;
		std::unordered_map<char, Ref<SubTexture2D>> s_TextureMap;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}