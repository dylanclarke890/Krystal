#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "Core/TimeStep.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

namespace Krys
{
  class KRYSTAL_API Application
  {
  private:
    static Application* s_Instance;
  public:
    static inline Application& Get() { return *s_Instance; }

  private:
    bool m_Running;
    std::unique_ptr<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    LayerStack m_LayerStack;
    float m_LastFrameTime;

    bool OnWindowClose(WindowCloseEvent& e);
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