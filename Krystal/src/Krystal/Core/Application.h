#pragma once

#include "Krystal/Core/Core.h"
#include "Krystal/Core/Window.h"
#include "Krystal/Core/LayerStack.h"
#include "Krystal/Core/TimeStep.h"

#include "Krystal/Events/Event.h"
#include "Krystal/Events/ApplicationEvent.h"

#include "Krystal/ImGui/ImGuiLayer.h"

namespace Krys
{
  class Application
  {
  private:
    static Application* s_Instance;
  public:
    static inline Application& Get() { return *s_Instance; }

  private:
    bool m_Running, m_Minimised;
    Scope<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    LayerStack m_LayerStack;
    float m_LastFrameTime;

    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);
  public:
    Application();
    virtual ~Application();

    void Run();
    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);

    inline Window& GetWindow() { return *m_Window; }
  };

  // To be defined in CLIENT
  Application* CreateApplication();
}