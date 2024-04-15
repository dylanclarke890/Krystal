#pragma once

#include "Application.h"
#include "Input/MouseButtons.h"
#include "Input/KeyCodes.h"
#include "Logging/Logger.h"
#include "Maths/Vector.h"
#include "Misc/Performance.h"
#include "Misc/Chrono.h"

namespace Krys
{
  Application::Application(float targetFps, Window *window, Input *input)
      : window(window), input(input), IsRunning(false), TargetFrameTimeMs(1000.0f / targetFps) {}

  void Application::Run()
  {
    window->SetEventCallback(KRYS_BIND_EVENT_FN(Application::OnEvent));
    window->Show(true);

    IsRunning = true;

    while (IsRunning)
    {
      int64 startCounter = Performance::GetTicks();

      window->BeginFrame();
      input->BeginFrame();
      {
      }
      input->EndFrame();
      window->EndFrame();

      int64 endCounter = Performance::GetTicks();
      float elapsedMs = Performance::TicksToMilliseconds(endCounter - startCounter);

      while (elapsedMs < TargetFrameTimeMs - 2)
      {
        Chrono::Sleep(1);
        endCounter = Performance::GetTicks();
        elapsedMs = Performance::TicksToMilliseconds(endCounter - startCounter);
      }

      while (elapsedMs < TargetFrameTimeMs)
      {
        endCounter = Performance::GetTicks();
        elapsedMs = Performance::TicksToMilliseconds(endCounter - startCounter);
      }

      Logger::Log("Frame time: %.02f ms.", elapsedMs);
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
    Logger::Log(event.GetName());

    if (event.Alt)
      Logger::Log("Alt was down");

    if (event.Shift)
      Logger::Log("Shift was down");

    if (event.Ctrl)
      Logger::Log("Ctrl was down");

    if (event.Buttons & MouseButton::Left)
      Logger::Log("Left button was down");

    if (event.Buttons & MouseButton::Right)
      Logger::Log("Right button was down");

    if (event.Buttons & MouseButton::Middle)
      Logger::Log("Middle button was down");

    if (event.Buttons & MouseButton::Thumb1)
      Logger::Log("Thumb1 button was down");

    if (event.Buttons & MouseButton::Thumb2)
      Logger::Log("Thumb2 button was down");

    return false;
  }

  bool Application::OnKeyEvent(KeyEvent &event)
  {
    Logger::Log(event.GetName());
    Logger::Log("Key: %d", (int)event.Key);

    Vector3D<float> vec1(1.0f, 1.0f, 1.0f);
    Vector3D<float> vec2(1.0f, 1.0f, 1.0f);

    Vector3D<float> sum = vec1 + vec2;

    Logger::Log("X: %f, Y: %f, Z: %f", sum.X, sum.Y, sum.Z);

    return false;
  }

  bool Application::OnShutdownEvent(ShutdownEvent &event)
  {
    IsRunning = false;
    Logger::Log(event.GetName());

    return true;
  }
  // #endregion Events
}