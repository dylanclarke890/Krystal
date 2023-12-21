#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Krys
{
  class KRYSTAL_API Application
  {
  private:
    std::unique_ptr<Window> m_Window;
    bool m_Running;
    LayerStack m_LayerStack;
  public:
    Application();
    virtual ~Application();

    void Run();
    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
  private:
    bool OnWindowClose(WindowCloseEvent& e);
  };

  // To be defined in CLIENT
  Application* CreateApplication();
}