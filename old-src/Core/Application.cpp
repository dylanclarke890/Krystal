#pragma once

#include "Core.h"
#include "Application.h"

#include "Input/MouseButtons.h"
#include "Input/KeyCodes.h"

#include "Graphics/Camera/Perspective.h"
#include "Graphics/NodeVisitors/NodeVisitorContext.h"
#include "Graphics/NodeVisitors/RenderVisitor.h"
#include "Graphics/Renderer.h"
#include "Graphics/VertexArray.h"

#include "Misc/Performance.h"
#include "Misc/Time.h"
#include "Misc/Chrono.h"

namespace Krys
{
  Application::Application(const string &name, int width, int height, float targetFps) noexcept
      : _window(Window::Create(name, width, height)), _isRunning(false), _targetFrameTimeMs(1000.0f / targetFps)
  {
  }

  void Application::Startup() noexcept
  {
    Input::Init();
    _window->Show();
  }

  void Application::Run() noexcept
  {
    _isRunning = true;
    float elapsedMs = 0;

    while (_isRunning)
    {
      int64 startCounter = Performance::GetTicks();
      BeginFrame();
      {
        Update(elapsedMs / 1000.0f);
      }
      EndFrame();
      int64 endCounter = Performance::GetTicks();
      elapsedMs = Performance::TicksToMilliseconds(endCounter - startCounter);

      while (elapsedMs < _targetFrameTimeMs - 2)
      {
        Chrono::Sleep(1);
        endCounter = Performance::GetTicks();
        elapsedMs = Performance::TicksToMilliseconds(endCounter - startCounter);
      }

      while (elapsedMs < _targetFrameTimeMs)
      {
        endCounter = Performance::GetTicks();
        elapsedMs = Performance::TicksToMilliseconds(endCounter - startCounter);
      }

      Time::Increment(elapsedMs);
    }
  }

  void Application::Stop() noexcept
  {
    _isRunning = false;
  }

  void Application::Shutdown() noexcept
  {
    Input::Shutdown();
  }

  void Application::BeginFrame() noexcept
  {
    _window->BeginFrame();
    Input::BeginFrame();
  }

  void Application::Update(float dt) noexcept
  {
    KRYS_PERFORMANCE_TIMER("Frame");
  }

  void Application::EndFrame() noexcept
  {
    _window->EndFrame();
    Input::EndFrame();
  }

#pragma region Events

  void Application::OnEvent(Event &event) noexcept
  {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<ShutdownEvent>(KRYS_BIND_EVENT_FN(Application::OnShutdownEvent));
    dispatcher.Dispatch<ResizeEvent>(KRYS_BIND_EVENT_FN(Application::OnResizeEvent));
  }

  bool Application::OnShutdownEvent(ShutdownEvent &event) noexcept
  {
    _isRunning = false;
    return true;
  }

  bool Application::OnResizeEvent(ResizeEvent &event) noexcept
  {
    KRYS_INFO("Window Resized: Width: %d, Height: %d", event.Width, event.Height);
    // TODO: we need to keep track of the width and height instead as we frequently change the viewport dimensions.
    return false;
  }

#pragma endregion Events
}