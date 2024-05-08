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
  static bool WireFrameMode = false;

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

    static auto pos1 = Vec3(-0.75f, +0.0f, 0.0f);
    static auto pos2 = Vec3(+0.25f, +0.0f, 0.0f);
    static auto pos3 = Vec3(+0.00f, -0.20f, 0.0f);
    static auto pos4 = Vec3(+0.00f, -0.80f, 0.0f);
    static auto size = Vec2(0.5f);
    static auto color1 = Vec4(0.8f, 0.6f, 0.7f, 1.0f);
    static auto color2 = Vec4(0.3f, 0.2f, 0.4f, 1.0f);
    static auto color3 = Vec4(color1.x, color1.y, color1.z, 0.5f);
    static auto texture = ctx->CreateTexture2D("textures/container.jpg");
    texture->GenerateMipmaps();

    float totalTimeElapsedInMs = 0;
    while (IsRunning)
    {
      KRYS_PERFORMANCE_TIMER("Frame");
      int64 startCounter = Performance::GetTicks();

      window->BeginFrame();
      input->BeginFrame();

      ctx->SetWireframeModeEnabled(WireFrameMode);

      Renderer2D::BeginScene();
      {
        ctx->Clear(ClearFlags::Color);
        Renderer2D::DrawQuad(pos1, size, color1);
        Renderer2D::DrawQuad(pos2, size, color2);
        Renderer2D::DrawQuad(pos3, size, texture);
        Renderer2D::DrawQuad(pos4, size, texture, color3);
      }
      Renderer2D::EndScene();
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

    if (event.GetEventType() == EventType::KeyPressed && event.Key == KeyCode::Space)
      WireFrameMode = !WireFrameMode;

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