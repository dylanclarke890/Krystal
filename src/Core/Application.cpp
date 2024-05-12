#pragma once

#include "Krystal.h"
#include "Application.h"

#include "Input/MouseButtons.h"
#include "Input/KeyCodes.h"

#include "Graphics/Camera/Perspective.h"
#include "Graphics/Renderer2D.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

#include "Misc/Performance.h"
#include "Maths/Maths.h"
#include "Misc/Time.h"
#include "Misc/Chrono.h"

#define ARRAY_COUNT(data) (sizeof(data) / sizeof(data[0]))

namespace Krys
{
  static bool WireFrameMode = false;

  Application::Application(float targetFps, Ref<Window> window)
      : window(window), ctx(window->GetGraphicsContext()),
        IsRunning(false), TargetFrameTimeMs(1000.0f / targetFps)
  {
    window->SetEventCallback(KRYS_BIND_EVENT_FN(Application::OnEvent));
    Input::Init();
    Renderer2D::Init(ctx);

    Camera = CreateRef<PerspectiveCamera>(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

    window->Show();
  }

  void Application::Run()
  {
    IsRunning = true;

    static auto size = Vec2(0.5f);

    static auto pos1 = Vec3(-0.75f, +0.0f, 0.0f);
    static auto pos2 = Vec3(+0.25f, +0.0f, 0.0f);
    static auto pos3 = Vec3(+0.00f, -0.20f, 0.0f);
    static auto pos4 = Vec3(+0.00f, -0.80f, 0.0f);

    static auto color1 = Vec4(0.8f, 0.6f, 0.7f, 1.0f);
    static auto color2 = Vec4(0.3f, 0.2f, 0.4f, 1.0f);
    static auto color3 = Vec4(color1.x, color1.y, color1.z, 0.5f);

    static auto texture = ctx->CreateTexture2D("textures/container.jpg");
    texture->GenerateMipmaps();

    static auto subTextureSpriteSize = Vec2(128.0f, 128.0f);
    static auto subTextureCellSize = Vec2(1.0f, 1.0f);
    static auto subTextureCoords = Vec2(0.25f, 1.0f);
    static auto subTexture = ctx->CreateSubTexture2D(texture, subTextureCoords, subTextureSpriteSize, subTextureCellSize);

    while (IsRunning)
    {
      // KRYS_LOG("Delta Time: %f", Time::GetDeltaMs());
      int64 startCounter = Performance::GetTicks();

      window->BeginFrame();
      Input::BeginFrame();
      {
        ctx->SetWireframeModeEnabled(WireFrameMode);
        Camera->OnUpdate(Time::GetDeltaSecs());

        Renderer2D::BeginScene(Camera);
        {
          ctx->Clear(ClearFlags::Color);
          Renderer2D::DrawQuad(pos1, size, color1);
          Renderer2D::DrawQuad(pos2, size, texture);
          Renderer2D::DrawQuad(pos3, size, texture, color3);
          Renderer2D::DrawQuad(pos4, size, subTexture);
        }
        Renderer2D::EndScene();
      }
      Input::EndFrame();
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

      Time::Increment(elapsedMs);
    }
  }

  void Application::Shutdown()
  {
    Renderer2D::Shutdown();
  }

#pragma region Events
  void Application::OnEvent(Event &event)
  {
    KRYS_INFO(event.GetName());

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseButtonReleasedEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseButtonEvent));
    dispatcher.Dispatch<MouseButtonPressedEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseButtonEvent));
    dispatcher.Dispatch<MouseScrollEvent>(KRYS_BIND_EVENT_FN(Application::OnMouseScrollEvent));
    dispatcher.Dispatch<KeyPressedEvent>(KRYS_BIND_EVENT_FN(Application::OnKeyEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(KRYS_BIND_EVENT_FN(Application::OnKeyEvent));
    dispatcher.Dispatch<ShutdownEvent>(KRYS_BIND_EVENT_FN(Application::OnShutdownEvent));
    dispatcher.Dispatch<ResizeEvent>(KRYS_BIND_EVENT_FN(Application::OnResizeEvent));

    Camera->OnEvent(event);
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

  bool Application::OnMouseScrollEvent(MouseScrollEvent &event)
  {
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
    return false;
  }

#pragma endregion Events
}