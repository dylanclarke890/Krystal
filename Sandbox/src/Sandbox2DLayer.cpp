#include "Sandbox2DLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

void Sandbox2DLayer::OnAttach()
{
}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(Krys::TimeStep ts)
{
  m_CameraController.OnUpdate(ts);
}

void Sandbox2DLayer::OnImGuiRender()
{
  ImGui::Begin("Settings");
  ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
  ImGui::End();
}

void Sandbox2DLayer::OnEvent(Krys::Event& e)
{
  m_CameraController.OnEvent(e);
}
