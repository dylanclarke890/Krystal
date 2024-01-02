#include "Sandbox2DLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2DLayer::Sandbox2DLayer()
  : Layer("Sandbox 2D"),
  m_CameraController(1280.0f / 720.0f, true),
  m_SquareColor(0.2f, 0.3f, 0.8f, 1.0f)
{
}

void Sandbox2DLayer::OnAttach()
{
	m_VertexArray = Krys::VertexArray::Create();
	m_Shader = Krys::Shader::Create("assets/shaders/FlatColor.krys");

	float vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

	Krys::Ref<Krys::VertexBuffer> vertexBuffer = Krys::VertexBuffer::Create(vertices, sizeof(vertices));
	Krys::Ref<Krys::IndexBuffer> indexBuffer = Krys::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

	vertexBuffer->SetLayout({
		{ Krys::ShaderDataType::Float3, "a_Position" }
	});
	m_VertexArray->AddVertexBuffer(vertexBuffer);
	m_VertexArray->SetIndexBuffer(indexBuffer);
}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(Krys::TimeStep ts)
{
	m_CameraController.OnUpdate(ts);

	Krys::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Krys::RenderCommand::Clear();

	Krys::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		Krys::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Krys::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	}
	Krys::Renderer2D::EndScene();
}

void Sandbox2DLayer::OnImGuiRender()
{
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
  ImGui::End();
}

void Sandbox2DLayer::OnEvent(Krys::Event& e)
{
  m_CameraController.OnEvent(e);
}
