#pragma once

#include <windows.h>
#include "Application.h"

namespace Krys
{
  Application::Application(Window *window)
      : window(window)
  {
  }

  void Application::Run()
  {
    window->Show(true);
    window->SetEventCallback(KRYS_BIND_EVENT_FN(Application::OnEvent));

    isRunning = true;
    while (isRunning)
    {
      window->BeginFrame();
      window->EndFrame();
    }
  }

  void Application::OnEvent(Event &event)
  {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseDownEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseEvent));
    dispatcher.Dispatch<MouseUpEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseEvent));
    dispatcher.Dispatch<ShutdownEvent>(KRYS_BIND_EVENT_FN(Application::OnShutdownEvent));
  }

  bool Application::OnMouseEvent(MouseEvent &event)
  {
    OutputDebugStringA(event.GetName());
    OutputDebugStringA("\n");

    return false;
  }

  bool Application::OnShutdownEvent(ShutdownEvent &event)
  {
    isRunning = false;
    OutputDebugStringA(event.GetName());
    OutputDebugStringA("\n");

    return true;
  }
}