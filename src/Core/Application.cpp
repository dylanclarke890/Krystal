#pragma once

#include <windows.h>
#include "Application.h"

namespace Krys
{
  Application::Application(Window *window) : window(window) {}

  void Application::Run()
  {
    window->SetEventCallback(KRYS_BIND_EVENT_FN(Application::OnEvent));
    window->Show(true);

    isRunning = true;
    while (isRunning)
    {
      window->BeginFrame();

      // TODO: do stuff here

      window->EndFrame();
    }
  }

  // #region Events
  void Application::OnEvent(Event &event)
  {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseDownEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseDownEvent));
    dispatcher.Dispatch<MouseUpEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseUpEvent));
    dispatcher.Dispatch<ShutdownEvent>(KRYS_BIND_EVENT_FN(Application::OnShutdownEvent));
  }

  bool Application::OnMouseDownEvent(MouseDownEvent &event)
  {
    OutputDebugStringA(event.GetName());
    OutputDebugStringA("\n");

    return false;
  }

  bool Application::OnMouseUpEvent(MouseUpEvent &event)
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
  // #endregion Events
}