#pragma once

#include "Core.h"
#include "Application.h"

#include "Input/MouseButtons.h"
#include "Input/KeyCodes.h"

#include "Graphics/Camera/Perspective.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

#include "Misc/Performance.h"
#include "Maths/Maths.h"
#include "Misc/Time.h"
#include "Misc/Chrono.h"

namespace Krys
{
  Application::Application(const char *name, int width, int height, float targetFps)
      : Window(Window::Create(name, width, height)), Context(Window->GetGraphicsContext()),
        IsRunning(false), TargetFrameTimeMs(1000.0f / targetFps)
  {
  }

  void Application::Startup()
  {
    Context->Init();
    Context->SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});

    Input::Init();
    Window->Show();
  }

  void Application::Run()
  {
    IsRunning = true;
    float elapsedMs = 0;

    while (IsRunning)
    {
      // KRYS_LOG("Delta Time: %f", Time::GetDeltaMs());
      int64 startCounter = Performance::GetTicks();
      {
        Update(elapsedMs);
      }
      int64 endCounter = Performance::GetTicks();
      elapsedMs = Performance::TicksToMilliseconds(endCounter - startCounter);

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

      Time::Increment(elapsedMs);
    }
  }

  void Application::Shutdown()
  {
    Input::Shutdown();
  }

#pragma region Events

  void Application::OnEvent(Event &event)
  {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<ShutdownEvent>(KRYS_BIND_EVENT_FN(Application::OnShutdownEvent));
    dispatcher.Dispatch<ResizeEvent>(KRYS_BIND_EVENT_FN(Application::OnResizeEvent));
  }

  bool Application::OnShutdownEvent(ShutdownEvent &event)
  {
    IsRunning = false;
    return true;
  }

  bool Application::OnResizeEvent(ResizeEvent &event)
  {
    KRYS_INFO("Window Resized: Width: %d, Height: %d", event.Width, event.Height);
    Context->SetViewport(event.Width, event.Height);
    return false;
  }

#pragma endregion Events
}