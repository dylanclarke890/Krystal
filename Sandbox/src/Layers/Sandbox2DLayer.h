#pragma once

#include "Krystal.h"

class Sandbox2DLayer : public Krys::Layer
{
private:
  Krys::OrthographicCameraController m_CameraController;
  Krys::Ref<Krys::Shader> m_Shader;
  Krys::Ref<Krys::VertexArray> m_VertexArray;

  glm::vec4 m_SquareColor;

public:
  Sandbox2DLayer();
  virtual ~Sandbox2DLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(Krys::TimeStep ts) override;
  virtual void OnImGuiRender() override;
  virtual void OnEvent(Krys::Event& e) override;
};