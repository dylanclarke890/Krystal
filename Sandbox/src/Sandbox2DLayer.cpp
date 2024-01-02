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
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Krys::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Krys::RenderCommand::Clear();

	Krys::Renderer::BeginScene(m_CameraController.GetCamera());

	m_Shader->Bind();
	std::dynamic_pointer_cast<Krys::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Krys::Renderer::Submit(m_Shader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Krys::Renderer::EndScene();
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
