#include "Sandbox2DLayer.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Sandbox2DLayer::Sandbox2DLayer()
  : Layer("Sandbox 2D"),
  m_CameraController(1280.0f / 720.0f, true),
  m_SquareColor(0.2f, 0.3f, 0.8f, 1.0f)
{
}

void Sandbox2DLayer::OnAttach()
{
	m_CheckerboardTexture = Krys::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = Krys::Texture2D::Create("assets/game/textures/rpg-pack-spritesheet.png");

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f, 0.0f };
}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(Krys::TimeStep ts)
{
	KRYS_PROFILE_FUNCTION();
	
	Krys::Renderer2D::ResetStats();
	
	m_CameraController.OnUpdate(ts);

	{
		KRYS_PROFILE_SCOPE("Renderer Prep");
		Krys::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Krys::RenderCommand::Clear();
	}
	{
		KRYS_PROFILE_SCOPE("Renderer Draw");
#if 0

		static float rotation = 0.0f;
		rotation += ts * 20.0f;

		Krys::Renderer2D::BeginScene(m_CameraController.GetCamera());
		{
			Krys::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), {0.8f, 0.2f, 0.3f, 1.0f});
			Krys::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			Krys::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
			Krys::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
			Krys::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.f);

			for (float y = -5.0f; y < 5.0f; y += 0.5f)
			{
				for (float x = -5.0f; x < 5.0f; x += 0.5f)
				{
					glm::vec4 color = { (x + 5.0f) / 10.f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
					Krys::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
				}
			}
		}
		Krys::Renderer2D::EndScene();
#endif

		if (Krys::Input::IsMouseButtonPressed(Krys::MouseCode::ButtonLeft))
		{
			auto [x, y] = Krys::Input::GetMousePosition();
			auto width = Krys::Application::Get().GetWindow().GetWidth();
			auto height = Krys::Application::Get().GetWindow().GetHeight();

			Krys::OrthographicCameraBounds bounds = m_CameraController.GetBounds();
			auto& pos = m_CameraController.GetCamera().GetPosition();

			x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
			m_Particle.Position = { x + pos.x, y + pos.y, 0.0f };
			
			for (int i = 0; i < 5; i++)
				m_ParticleSystem.Emit(m_Particle);
		}

		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());

		Krys::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Krys::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.1f}, {1.0f, 1.0f}, m_SpriteSheet);
		Krys::Renderer2D::EndScene();
	}
}

void Sandbox2DLayer::OnImGuiRender()
{
	KRYS_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	{
		auto stats = Krys::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Textures: %d", stats.Textures);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	}
	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Krys::Event& e)
{
  m_CameraController.OnEvent(e);
}
