#include "krys-pch.h"
#include "Krystal/Core/Application.h"

#include "Krystal/Core/Input.h"
#include "Krystal/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Krys
{
  Application* Application::s_Instance = nullptr;

  Application::Application()
    : m_Running(true), m_Minimised(false), m_LastFrameTime(0.0f)
  {
    KRYS_PROFILE_FUNCTION();

    KRYS_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = Window::Create();
    m_Window->SetEventCallback(KRYS_BIND_EVENT_FN(Application::OnEvent));

    Renderer::Init();

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
  }
  
  Application::~Application() {
    Renderer::Shutdown();
  }

  void Application::Run()
  {
    KRYS_PROFILE_FUNCTION();

    while (m_Running) 
    {
      KRYS_PROFILE_SCOPE("RunLoop");

      float time = (float)glfwGetTime(); // TODO: Platform::GetTime
      TimeStep ts(time - m_LastFrameTime);
      m_LastFrameTime = time;

      if (!m_Minimised)
      {
        {
          KRYS_PROFILE_SCOPE("LayerStack OnUpdate");

          for (Layer* layer : m_LayerStack)
            layer->OnUpdate(ts);
        }
      }

      m_ImGuiLayer->Begin();
      {
        KRYS_PROFILE_SCOPE("LayerStack OnImGuiRender");
        for (Layer* layer : m_LayerStack)
          layer->OnImGuiRender();
      }
      m_ImGuiLayer->End();

      m_Window->OnUpdate();
    }
  }

  void Application::OnEvent(Event& e)
  {
    KRYS_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(KRYS_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(KRYS_BIND_EVENT_FN(Application::OnWindowResize));

    for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
    {
      if (e.Handled)
        break;

      (*it)->OnEvent(e);
    }
  }

  void Application::PushLayer(Layer* layer)
  {
    KRYS_PROFILE_FUNCTION();

    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* overlay)
  {
    KRYS_PROFILE_FUNCTION();

    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
  }

  bool Application::OnWindowClose(WindowCloseEvent& e)
  {
    m_Running = false;
    return true;
  }

  bool Application::OnWindowResize(WindowResizeEvent& e)
  {
    KRYS_PROFILE_FUNCTION();

    if (e.GetWidth() == 0 || e.GetHeight() == 0)
    {
      m_Minimised = true;
      return false;
    }

    m_Minimised = false;
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
    
    return false;
  }
}