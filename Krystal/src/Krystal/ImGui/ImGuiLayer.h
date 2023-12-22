#pragma once

#include "Krystal/Layer.h"
#include "Krystal/Events/ApplicationEvent.h"
#include "Krystal/Events/KeyEvent.h"
#include "Krystal/Events/MouseEvent.h"

namespace Krys
{
  class KRYSTAL_API ImGuiLayer : public Layer
  {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnEvent(Event& event) override;
private:
  float m_Time = 0.0f;

  // Events
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
  bool OnMouseMovedEvent(MouseMovedEvent& e);
  bool OnMouseScrolledEvent(MouseScrolledEvent& e);
  bool OnKeyTypedEvent(KeyTypedEvent& e);
  bool OnKeyPressedEvent(KeyPressedEvent& e);
  bool OnKeyReleasedEvent(KeyReleasedEvent& e);
  bool OnWindowResizedEvent(WindowResizeEvent& e);
  };
}