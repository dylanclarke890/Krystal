#pragma once

#include "Krystal.h"
#include "Application.h"

#include "Input/MouseButtons.h"
#include "Input/KeyCodes.h"

#include "Graphics/Renderer2D.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

#include "Misc/Performance.h"
#include "Maths/Maths.h"
#include "Misc/Chrono.h"

#define ARRAY_COUNT(data) (sizeof(data) / sizeof(data[0]))

namespace Krys
{
  static Vec3 offset(0.0f);

  Application::Application(float targetFps, Ref<Window> window, Ref<Input> input)
      : window(window), input(input), ctx(window->GetGraphicsContext()),
        IsRunning(false), TargetFrameTimeMs(1000.0f / targetFps)
  {
    window->SetEventCallback(KRYS_BIND_EVENT_FN(Application::OnEvent));
    window->Show(true);

    Renderer2D::Init(ctx);
  }

  void Application::Run()
  {
    IsRunning = true;

    float totalTimeElapsedInMs = 0;
    while (IsRunning)
    {
      PerformanceTimer frameTimer("Frame");
      int64 startCounter = Performance::GetTicks();

      static auto pos = Vec3(-0.5f, -0.5f, 0.0f);
      static auto size = Vec2(1.0f);
      static auto color = Vec4(0.8f, 0.6f, 0.7f, 1.0f);

      window->BeginFrame();
      input->BeginFrame();
      Renderer2D::Begin();
      {
        ctx->Clear(ClearFlags::Color);
        Renderer2D::DrawQuad(pos, size, color);
      }
      Renderer2D::End();
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

      totalTimeElapsedInMs += elapsedMs;
    }
  }

  void Application::Shutdown()
  {
    Renderer2D::Shutdown();
  }

  // #region Events
  void Application::OnEvent(Event &event)
  {
    KRYS_INFO(event.GetName());

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseButtonReleasedEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseButtonEvent));
    dispatcher.Dispatch<MouseButtonPressedEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseButtonEvent));
    dispatcher.Dispatch<KeyPressedEvent>(KRYS_BIND_EVENT_FN(Application::OnKeyEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(KRYS_BIND_EVENT_FN(Application::OnKeyEvent));
    dispatcher.Dispatch<ShutdownEvent>(KRYS_BIND_EVENT_FN(Application::OnShutdownEvent));
    dispatcher.Dispatch<ResizeEvent>(KRYS_BIND_EVENT_FN(Application::OnResizeEvent));
  }

  bool Application::OnMouseButtonEvent(MouseButtonEvent &event)
  {
    if (event.Alt)
      KRYS_INFO("Alt was down");

    if (event.Shift)
      KRYS_INFO("Shift was down");

    if (event.Ctrl)
      KRYS_INFO("Ctrl was down");

    if (event.Buttons & MouseButton::Left)
      KRYS_INFO("Left button was down");

    if (event.Buttons & MouseButton::Right)
      KRYS_INFO("Right button was down");

    if (event.Buttons & MouseButton::Middle)
      KRYS_INFO("Middle button was down");

    if (event.Buttons & MouseButton::Thumb1)
      KRYS_INFO("Thumb1 button was down");

    if (event.Buttons & MouseButton::Thumb2)
      KRYS_INFO("Thumb2 button was down");

    return false;
  }

  bool Application::OnKeyEvent(KeyEvent &event)
  {
    KRYS_INFO("Key: %d", (int)event.Key);

    if (event.Key == KeyCode::UpArrow)
    {
      offset.z -= 0.01f;
    }

    if (event.Key == KeyCode::DownArrow)
    {
      offset.z += 0.01f;
    }

    if (event.Key == KeyCode::LeftArrow)
    {
      offset.x -= 0.01f;
    }

    if (event.Key == KeyCode::RightArrow)
    {
      offset.x += 0.01f;
    }

    return false;
  }

  bool Application::OnShutdownEvent(ShutdownEvent &event)
  {
    IsRunning = false;
    Shutdown();
    return true;
  }

  bool Application::OnResizeEvent(ResizeEvent &event)
  {
    KRYS_INFO("Width: %d, Height: %d", event.Width, event.Height);
    ctx->SetViewport(event.Width, event.Height);
    return true;
  }

  // #endregion Events
}