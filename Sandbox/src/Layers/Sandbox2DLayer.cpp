#include "Sandbox2DLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

template<typename Fn>
class Timer
{
private:
	const char* m_Name;
	Fn m_Func;
	bool m_Stopped;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTime, m_EndTime;
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		Stop();
	}

	void Stop()
	{
		if (m_Stopped)
			return;
		
		m_EndTime = std::chrono::high_resolution_clock::now();
		m_Stopped = true;

		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTime).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(m_EndTime).time_since_epoch().count();

		KRYS_CORE_ASSERT(start < end, "PROFILER ERROR: Start time was greater than end time!");

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfilerResult profilerResult) { m_ProfilerResults.push_back(profilerResult); })

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
	PROFILE_SCOPE("Sandbox2DLayer::OnUpdate");
	
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		PROFILE_SCOPE("Renderer Prep");
		Krys::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Krys::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		Krys::Renderer2D::BeginScene(m_CameraController.GetCamera());
		{
			Krys::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			Krys::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
			Krys::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		}
		Krys::Renderer2D::EndScene();
	}
}

void Sandbox2DLayer::OnImGuiRender()
{
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfilerResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}

	m_ProfilerResults.clear();
	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Krys::Event& e)
{
  m_CameraController.OnEvent(e);
}
