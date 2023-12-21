#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace Krys
{
  class KRYSTAL_API Application
  {
  private:
    std::unique_ptr<Window> m_Window;
    bool m_Running;
  public:
    Application();
    virtual ~Application();

    void Run();
    void OnEvent(Event& e);
  private:
    bool OnWindowClose(WindowCloseEvent& e);
  };

  // To be defined in CLIENT
  Application* CreateApplication();
}