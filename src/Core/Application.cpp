#pragma once

#include <windows.h>
#include "Application.h"

namespace Krys
{
  static bool OnAppEvent(void *context, Event &event)
  {
    return static_cast<Application *>(context)->OnEvent(event);
  }

  Application::Application(Window *window)
      : window(window)
  {
  }

  void Application::Run()
  {
    window->Show(true);
    window->SetEventCallback(this, &OnAppEvent);

    isRunning = true;
    while (isRunning)
    {
      window->BeginFrame();
      window->EndFrame();
    }
  }

  bool Application::OnEvent(Event &event)
  {
    if (event.GetEventType() == EventType::Shutdown)
      isRunning = false;

    OutputDebugStringA(event.GetName());
    OutputDebugStringA("\n");

    return false;
  }
}