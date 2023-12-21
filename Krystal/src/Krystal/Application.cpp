#include "krys-pch.h"
#include "Application.h"

namespace Krys
{
  Application::Application(): m_Running(true)
  {
    m_Window = std::unique_ptr<Window>(Window::Create());
  }
  
  Application::~Application()
  {
  }

  void Application::Run()
  {
    while (m_Running) 
    {
      m_Window->OnUpdate();
    }
  }
}