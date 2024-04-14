#pragma once

#include <windows.h>
#include "Application.h"
#include "Input/MouseButtons.h"
#include "Input/KeyCodes.h"
#include "Logging/Logger.h"
#include "Maths/Vector.h"

namespace Krys
{
  Application::Application(Window *window, Input *input) : window(window), input(input) {}

  void Application::Run()
  {
    window->SetEventCallback(KRYS_BIND_EVENT_FN(Application::OnEvent));
    window->Show(true);

    IsRunning = true;
    while (IsRunning)
    {
      window->BeginFrame();
      input->BeginFrame();

      // TODO: do stuff here...

      input->EndFrame();
      window->EndFrame();
    }
  }

  // #region Events
  void Application::OnEvent(Event &event)
  {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseButtonReleasedEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseButtonEvent));
    dispatcher.Dispatch<MouseButtonPressedEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseButtonEvent));
    dispatcher.Dispatch<KeyPressedEvent>(KRYS_BIND_EVENT_FN(Application::OnKeyEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(KRYS_BIND_EVENT_FN(Application::OnKeyEvent));
    dispatcher.Dispatch<ShutdownEvent>(KRYS_BIND_EVENT_FN(Application::OnShutdownEvent));
  }

  bool Application::OnMouseButtonEvent(MouseButtonEvent &event)
  {
    Logger::Log(LogLevel::Info, event.GetName());

    if (event.Alt)
      Logger::Log(LogLevel::Info, "Alt was down");

    if (event.Shift)
      Logger::Log(LogLevel::Info, "Shift was down");

    if (event.Ctrl)
      Logger::Log(LogLevel::Info, "Ctrl was down");

    if (event.Buttons & MouseButton::Left)
      Logger::Log(LogLevel::Info, "Left button was down");

    if (event.Buttons & MouseButton::Right)
      Logger::Log(LogLevel::Info, "Right button was down");

    if (event.Buttons & MouseButton::Middle)
      Logger::Log(LogLevel::Info, "Middle button was down");

    if (event.Buttons & MouseButton::Thumb1)
      Logger::Log(LogLevel::Info, "Thumb1 button was down");

    if (event.Buttons & MouseButton::Thumb2)
      Logger::Log(LogLevel::Info, "Thumb2 button was down");

    return false;
  }

  bool Application::OnKeyEvent(KeyEvent &event)
  {
    Logger::Log(LogLevel::Info, event.GetName());
    Logger::Log(LogLevel::Info, "Key: %d", (int)event.Key);

    Vector3D<float> vec1(1.0f, 1.0f, 1.0f);
    Vector3D<float> vec2(1.0f, 1.0f, 1.0f);

    Vector3D<float> sum = vec1 + vec2;

    Logger::Log(LogLevel::Info, "X: %f, Y: %f, Z: %f", sum.X, sum.Y, sum.Z);

    return false;
  }

  bool Application::OnShutdownEvent(ShutdownEvent &event)
  {
    IsRunning = false;
    Logger::Log(LogLevel::Info, event.GetName());

    return true;
  }
  // #endregion Events
}