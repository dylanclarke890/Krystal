#pragma once

#include <glad.h>

#include "Krystal.h"
#include "Application.h"

#include "Input/MouseButtons.h"
#include "Input/KeyCodes.h"

#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"

#include "Misc/Performance.h"
#include "Misc/Maths.h"
#include "Misc/Chrono.h"

#define ARRAY_COUNT(data) (sizeof(data) / sizeof(data[0]))

namespace Krys
{
  Application::Application(float targetFps, Window *window, Input *input)
      : window(window), input(input), ctx(window->GetGraphicsContext()),
        IsRunning(false), TargetFrameTimeMs(1000.0f / targetFps) {}

  void Application::Run()
  {
    window->SetEventCallback(KRYS_BIND_EVENT_FN(Application::OnEvent));
    window->Show(true);

    ctx->SetFaceCulling(CullMode::Back);
    ctx->SetWindingOrder(WindingOrder::Clockwise);

    IsRunning = true;

    const float vertexData[] = {
        0.25f,
        0.25f,
        -1.25f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,

        0.25f,
        -0.25f,
        -1.25f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,

        -0.25f,
        0.25f,
        -1.25f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,

        0.25f,
        -0.25f,
        -1.25f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,

        -0.25f,
        -0.25f,
        -1.25f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,

        -0.25f,
        0.25f,
        -1.25f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,

        0.25f,
        0.25f,
        -2.75f,
        1.0f,
        0.8f,
        0.8f,
        0.8f,
        1.0f,

        -0.25f,
        0.25f,
        -2.75f,
        1.0f,
        0.8f,
        0.8f,
        0.8f,
        1.0f,

        0.25f,
        -0.25f,
        -2.75f,
        1.0f,
        0.8f,
        0.8f,
        0.8f,
        1.0f,

        0.25f,
        -0.25f,
        -2.75f,
        1.0f,
        0.8f,
        0.8f,
        0.8f,
        1.0f,

        -0.25f,
        0.25f,
        -2.75f,
        1.0f,
        0.8f,
        0.8f,
        0.8f,
        1.0f,

        -0.25f,
        -0.25f,
        -2.75f,
        1.0f,
        0.8f,
        0.8f,
        0.8f,
        1.0f,

        -0.25f,
        0.25f,
        -1.25f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,

        -0.25f,
        -0.25f,
        -1.25f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,

        -0.25f,
        -0.25f,
        -2.75f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,

        -0.25f,
        0.25f,
        -1.25f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,

        -0.25f,
        -0.25f,
        -2.75f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,

        -0.25f,
        0.25f,
        -2.75f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,

        0.25f,
        0.25f,
        -1.25f,
        1.0f,
        0.5f,
        0.5f,
        0.0f,
        1.0f,

        0.25f,
        -0.25f,
        -2.75f,
        1.0f,
        0.5f,
        0.5f,
        0.0f,
        1.0f,

        0.25f,
        -0.25f,
        -1.25f,
        1.0f,
        0.5f,
        0.5f,
        0.0f,
        1.0f,

        0.25f,
        0.25f,
        -1.25f,
        1.0f,
        0.5f,
        0.5f,
        0.0f,
        1.0f,

        0.25f,
        0.25f,
        -2.75f,
        1.0f,
        0.5f,
        0.5f,
        0.0f,
        1.0f,

        0.25f,
        -0.25f,
        -2.75f,
        1.0f,
        0.5f,
        0.5f,
        0.0f,
        1.0f,

        0.25f,
        0.25f,
        -2.75f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,

        0.25f,
        0.25f,
        -1.25f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,

        -0.25f,
        0.25f,
        -1.25f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,

        0.25f,
        0.25f,
        -2.75f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,

        -0.25f,
        0.25f,
        -1.25f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,

        -0.25f,
        0.25f,
        -2.75f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,

        0.25f,
        -0.25f,
        -2.75f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,

        -0.25f,
        -0.25f,
        -1.25f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,

        0.25f,
        -0.25f,
        -1.25f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,

        0.25f,
        -0.25f,
        -2.75f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,

        -0.25f,
        -0.25f,
        -2.75f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,

        -0.25f,
        -0.25f,
        -1.25f,
        1.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,
    };

    VertexBuffer *vb = ctx->CreateVertexBuffer(sizeof(vertexData));
    vb->SetData(vertexData, sizeof(vertexData));
    vb->SetLayout({{ShaderDataType::Float4, "position"}, {ShaderDataType::Float4, "color"}});

    VertexArray *va = ctx->CreateVertexArray();
    va->AddVertexBuffer(vb);

    Shader *shader = ctx->CreateShader();
    shader->Load(ShaderType::Vertex, "shader.vert");
    shader->Load(ShaderType::Fragment, "shader.frag");
    shader->Link();
    shader->Bind();

    Vec2 offset(0.5f);
    Mat4 proj = glm::perspective(glm::radians(90.0f), ((float)window->GetWidth() / (float)window->GetHeight()), 0.1f, 10.0f);

    shader->SetUniform("offset", offset);
    shader->SetUniform("perspectiveMatrix", proj);

    float totalTimeElapsedInMs = 0;
    while (IsRunning)
    {
      PerformanceTimer frameTimer("Frame");
      int64 startCounter = Performance::GetTicks();

      window->BeginFrame();
      input->BeginFrame();
      {
        glDrawArrays(GL_TRIANGLES, 0, 36);
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

      totalTimeElapsedInMs += elapsedMs;
    }

    delete va;
    delete vb;
    delete shader;
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
    return false;
  }

  bool Application::OnShutdownEvent(ShutdownEvent &event)
  {
    IsRunning = false;
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