#pragma once

#include "Krystal.h"

class Sandbox2DLayer : public Krys::Layer
{
private:
  Krys::OrthographicCameraController m_CameraController;
  Krys::Ref<Krys::Shader> m_Shader;
  Krys::Ref<Krys::VertexArray> m_VertexArray;

  glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

public:
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(Krys::TimeStep ts) override;
  virtual void OnImGuiRender() override;
  virtual void OnEvent(Krys::Event& e) override;
};