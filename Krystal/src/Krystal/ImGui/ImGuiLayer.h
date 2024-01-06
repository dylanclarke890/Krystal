#pragma once

#include "Krystal/Core/Layer.h"

#include "Krystal/Events/ApplicationEvent.h"
#include "Krystal/Events/KeyEvent.h"
#include "Krystal/Events/MouseEvent.h"

namespace Krys
{
  class ImGuiLayer : public Layer
  {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Event& e) override;

    void Begin();
    void End();
private:
  float m_Time = 0.0f;
  };
}