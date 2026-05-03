#pragma once

#include "Wasteland.h"
#include <Wasteland/Renderer/Texture.h>

#include "ParticleSystem.h"

class Sandbox2D : public Wasteland::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Wasteland::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Wasteland::Event& e) override;
private:
	Wasteland::OrthographicCameraController m_CameraController;

	// Temp
	Wasteland::Ref<Wasteland::VertexArray> m_SquareVA;
	Wasteland::Ref<Wasteland::Shader> m_FlatColorShader;

	Wasteland::Ref<Wasteland::Texture2D> m_CheckerboardTexture;
	Wasteland::Ref<Wasteland::Texture2D> m_SpriteSheet;
	Wasteland::Ref<Wasteland::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, Wasteland::Ref<Wasteland::SubTexture2D>> s_TextureMap;
};