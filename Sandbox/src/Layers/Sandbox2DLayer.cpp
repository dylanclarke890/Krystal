#include "Sandbox2DLayer.h"

#include <imgui/imgui.h>
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
}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(Krys::TimeStep ts)
{
	KRYS_PROFILE_FUNCTION();
	
	m_CameraController.OnUpdate(ts);

	{
		KRYS_PROFILE_SCOPE("Renderer Prep");
		Krys::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Krys::RenderCommand::Clear();
	}

	{
		KRYS_PROFILE_SCOPE("Renderer Draw");

		static float rotation = 0.0f;
		rotation += ts * 20.0f;

		Krys::Renderer2D::BeginScene(m_CameraController.GetCamera());
		{
			Krys::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
			Krys::Renderer2D::DrawQuad({ 0.8f, -1.5f }, { 0.5f, 0.75f }, { 0.5f, 0.3f, 0.8f, 1.0f });
			Krys::Renderer2D::DrawQuad({ 2.5f, -3.5f }, { 0.5f, 0.75f }, { 0.2f, 0.6f, 0.8f, 1.0f });
			Krys::Renderer2D::DrawQuad({ 2.5f, -3.5f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.f);
			Krys::Renderer2D::DrawRotatedQuad({ 2.5f, -3.5f }, { 10.0f, 10.0f }, rotation, m_CheckerboardTexture, 20.f);
		}
		Krys::Renderer2D::EndScene();
	}
}

void Sandbox2DLayer::OnImGuiRender()
{
	KRYS_PROFILE_FUNCTION();
}

void Sandbox2DLayer::OnEvent(Krys::Event& e)
{
  m_CameraController.OnEvent(e);
}
