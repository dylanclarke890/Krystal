#pragma once

#include <Krystal.h>

class DemoLayer : public Krys::Layer
{
private:
  Krys::ShaderLibrary m_ShaderLibrary;
  Krys::Ref<Krys::Shader> m_Shader, m_FlatColorShader, m_TextureShader;
  Krys::Ref<Krys::VertexArray> m_TriangleVertexArray, m_SquareVertexArray;
  Krys::Ref<Krys::Texture2D> m_CheckerboardTexture, m_MGTexture;
  Krys::OrthographicCameraController m_CameraController;
  glm::vec3 m_SquareColor;

public:
  DemoLayer();
  virtual void OnImGuiRender() override;
  virtual void OnUpdate(Krys::TimeStep ts) override;
  virtual void OnEvent(Krys::Event& e) override;
};
