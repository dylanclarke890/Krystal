#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Krystal/Renderer/Shader.h"
#include "Krystal/Renderer/Buffer.h"
#include "Krystal/Renderer/VertexArray.h"
#include "Krystal/Renderer/OrthographicCamera.h"

namespace Krys
{
  class KRYSTAL_API Application
  {
  private:
    std::unique_ptr<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    bool m_Running;
    LayerStack m_LayerStack;
    bool OnWindowClose(WindowCloseEvent& e);
    static Application* s_Instance;

  public:
    Application();
    virtual ~Application();

    void Run();
    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);

    inline Window& GetWindow() { return *m_Window; }
    inline static Application& Get() { return *s_Instance; }
  };

  // To be defined in CLIENT
  Application* CreateApplication();
}