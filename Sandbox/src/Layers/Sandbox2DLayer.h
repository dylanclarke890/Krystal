#pragma once

#include <Krystal.h>

#include <Krystal/Utilities/ParticleSystem.h>

class Sandbox2DLayer : public Krys::Layer
{
private:
  Krys::OrthographicCameraController m_CameraController;

  Krys::Ref<Krys::Texture2D> m_CheckerboardTexture;
  Krys::Ref<Krys::Texture2D> m_SpriteSheet;
  glm::vec4 m_SquareColor;

  Krys::ParticleProps m_Particle;
  Krys::ParticleSystem m_ParticleSystem;

public:
  Sandbox2DLayer();
  virtual ~Sandbox2DLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(Krys::TimeStep ts) override;
  virtual void OnImGuiRender() override;
  virtual void OnEvent(Krys::Event& e) override;
};