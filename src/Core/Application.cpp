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

    dispatcher.Dispatch<MouseButtonReleasedEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseButtonEvent));
    dispatcher.Dispatch<MouseButtonPressedEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseButtonEvent));
    dispatcher.Dispatch<ShutdownEvent>(KRYS_BIND_EVENT_FN(Application::OnShutdownEvent));
  }

  bool Application::OnMouseButtonEvent(MouseButtonEvent &event)
  {
    OutputDebugStringA(event.GetName());
    OutputDebugStringA("\n");

    if (event.Alt)
    {
      OutputDebugStringA("Alt was down");
      OutputDebugStringA("\n");
    }

    if (event.Shift)
    {
      OutputDebugStringA("Shift was down");
      OutputDebugStringA("\n");
    }

    if (event.Ctrl)
    {
      OutputDebugStringA("Ctrl was down");
      OutputDebugStringA("\n");
    }

    if (event.Buttons & MouseButton::Left)
    {
      OutputDebugStringA("Left button was down");
      OutputDebugStringA("\n");
    }

    if (event.Buttons & MouseButton::Right)
    {
      OutputDebugStringA("Right button was down");
      OutputDebugStringA("\n");
    }

    if (event.Buttons & MouseButton::Middle)
    {
      OutputDebugStringA("Middle button was down");
      OutputDebugStringA("\n");
    }

    if (event.Buttons & MouseButton::Thumb1)
    {
      OutputDebugStringA("Thumb1 button was down");
      OutputDebugStringA("\n");
    }

    if (event.Buttons & MouseButton::Thumb2)
    {
      OutputDebugStringA("Thumb2 button was down");
      OutputDebugStringA("\n");
    }

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