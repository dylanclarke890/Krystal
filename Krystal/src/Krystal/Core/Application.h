#pragma once

#include "Krystal/Core/Core.h"
#include "Krystal/Core/Window.h"
#include "Krystal/Core/LayerStack.h"
#include "Krystal/Core/TimeStep.h"

#include "Krystal/Events/Event.h"
#include "Krystal/Events/ApplicationEvent.h"

#include "Krystal/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Krys
{
  class Application
  {
  private:
    static Application* s_Instance;
    bool m_Running, m_Minimised;
    Scope<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    LayerStack m_LayerStack;
    float m_LastFrameTime;

    friend int ::main(int argc, char** argv);
  public:
    Application();
    virtual ~Application();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);

    inline Window& GetWindow() { return *m_Window; }
  
    static inline Application& Get() { return *s_Instance; }
  private:
    void Run();
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);
  };

  // To be defined in CLIENT
  Application* CreateApplication();
}