#include <Wasteland.h>
#include "Wasteland/Core/EntryPoint.h"

#include <Platform/OpenGL/OpenGLShader.h>
#include <Wasteland/Renderer/Texture.h>

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

class ExampleLayer : public Wasteland::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = Wasteland::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		Wasteland::Ref<Wasteland::VertexBuffer> vertexBuffer = Wasteland::VertexBuffer::Create(vertices, sizeof(vertices));
		Wasteland::BufferLayout layout = {
			{ Wasteland::ShaderDataType::Float3, "a_Position" },
			{ Wasteland::ShaderDataType::Float4, "a_Color" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Wasteland::Ref<Wasteland::IndexBuffer> indexBuffer = Wasteland::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Wasteland::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		};

		Wasteland::Ref<Wasteland::VertexBuffer> quadVB = Wasteland::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		quadVB->SetLayout({
			{ Wasteland::ShaderDataType::Float3, "a_Position" }, 
			{ Wasteland::ShaderDataType::Float2, "a_TexCoord" },
		});
		m_SquareVA->AddVertexBuffer(quadVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Wasteland::Ref<Wasteland::IndexBuffer> quadIB = Wasteland::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(quadIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Wasteland::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Wasteland::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("Texture", "assets/shaders/Texture.glsl");

		m_Texture = Wasteland::Texture2D::Create("assets/textures/Checkerboard.png");
		m_FrameTexture = Wasteland::Texture2D::Create("assets/textures/Frame.png");

		std::dynamic_pointer_cast<Wasteland::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Wasteland::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Wasteland::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Wasteland::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Wasteland::RenderCommand::Clear();

		Wasteland::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Wasteland::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Wasteland::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_FrameTexture->Bind();
		Wasteland::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Wasteland::Renderer::Submit(m_Shader, m_VertexArray);

		Wasteland::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::End();

	}

	void OnEvent(Wasteland::Event& e) override
	{
		m_CameraController.OnEvent(e);

		if (e.GetEventType() == Wasteland::EventType::WindowResize)
		{
			auto& re = (Wasteland::WindowResizeEvent&)e;

			//float zoom = (float)re.GetWidth() / 1280.0f;
			//m_CameraController.SetZoomLevel(zoom);
		}
	}
private:
	Wasteland::ShaderLibrary m_ShaderLibrary;
	Wasteland::Ref<Wasteland::Shader> m_Shader;
	Wasteland::Ref<Wasteland::VertexArray> m_VertexArray;

	Wasteland::Ref<Wasteland::Shader> m_FlatColorShader;
	Wasteland::Ref<Wasteland::VertexArray> m_SquareVA;

	Wasteland::Ref<Wasteland::Texture2D> m_Texture, m_FrameTexture;

	Wasteland::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

namespace Wasteland {

	class DemonCoreEditor : public Application
	{
	public:
		DemonCoreEditor()
		{
			// PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~DemonCoreEditor()
		{

		}

	};

	Application* CreateApplication()
	{
		return new DemonCoreEditor();
	}

}