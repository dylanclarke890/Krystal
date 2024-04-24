#pragma once

#include <glad.h>

#include "Krystal.h"
#include "Application.h"

#include "Input/MouseButtons.h"
#include "Input/KeyCodes.h"

#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"

#include "Misc/Performance.h"
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

    IsRunning = true;

    const float vertexData[] = {
        0.0f,
        0.5f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.5f,
        -0.366f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        -0.5f,
        -0.366f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
    };

    VertexBuffer *vb = ctx->CreateVertexBuffer(sizeof(vertexData));
    vb->SetData(vertexData, sizeof(vertexData));
    vb->SetLayout({{ShaderDataType::Float4, "position"}, {ShaderDataType::Float4, "color"}});

    VertexArray *va = ctx->CreateVertexArray();
    va->AddVertexBuffer(vb);

    Shader *shader = ctx->CreateShader();
    shader->Bind();
    shader->Load(ShaderType::Vertex, "shader.vert");
    shader->Load(ShaderType::Fragment, "shader.frag");
    shader->Link();

    float totalTimeElapsedInMs = 0;
    while (IsRunning)
    {
      int64 startCounter = Performance::GetTicks();

      window->BeginFrame();
      input->BeginFrame();
      {
        const float loopDuration = 5.0f;
        const float scale = 3.14159f * 2.0f / loopDuration;

        float currTimeThroughLoop = fmodf(totalTimeElapsedInMs / 1000.0f, loopDuration);
        float xOffset = cosf(currTimeThroughLoop * scale) * 0.5f;
        float yOffset = sinf(currTimeThroughLoop * scale) * 0.5f;

        std::vector<float> newData(ARRAY_COUNT(vertexData));
        memcpy(&newData[0], vertexData, sizeof(vertexData));
        for (int i = 0; i < ARRAY_COUNT(vertexData); i += 4)
        {
          newData[i] += xOffset;
          newData[i + 1] += yOffset;
        }

        vb->SetData(&newData[0], sizeof(vertexData));

        glDrawArrays(GL_TRIANGLES, 0, 3);
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

      KRYS_INFO("Frame time: %.02f ms.", elapsedMs);
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