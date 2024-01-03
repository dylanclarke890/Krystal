#pragma once

#include "Krystal.h"

class Sandbox2DLayer : public Krys::Layer
{
private:
  Krys::OrthographicCameraController m_CameraController;

  Krys::Ref<Krys::Texture2D> m_CheckerboardTexture;
  glm::vec4 m_SquareColor;

  struct ProfilerResult
  {
    const char* Name;
    float Time;
  };

  std::vector<Sandbox2DLayer::ProfilerResult> m_ProfilerResults;

public:
  Sandbox2DLayer();
  virtual ~Sandbox2DLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(Krys::TimeStep ts) override;
  virtual void OnImGuiRender() override;
  virtual void OnEvent(Krys::Event& e) override;
};