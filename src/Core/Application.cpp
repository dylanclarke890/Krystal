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
  static Vec3 offset(0.0f);

  Application::Application(float targetFps, Window *window, Input *input)
      : window(window), input(input), ctx(window->GetGraphicsContext()),
        IsRunning(false), TargetFrameTimeMs(1000.0f / targetFps)
  {
    window->SetEventCallback(KRYS_BIND_EVENT_FN(Application::OnEvent));
    window->Show(true);

    ctx->SetFaceCulling(CullMode::Back);
    ctx->SetWindingOrder(WindingOrder::Clockwise);

    ctx->SetDepthTestingEnabled(true);
    ctx->SetDepthClampRange(0.0f, 1.0f);
    ctx->SetDepthTestFunc(DepthTestFunc::EqualOrLess);
    ctx->SetClearDepth(1.0f);
  }

  void Application::Run()
  {
    IsRunning = true;

#pragma region Test Data

    const int numberOfVertices = 36;

#define RIGHT_EXTENT 0.8f
#define LEFT_EXTENT -RIGHT_EXTENT
#define TOP_EXTENT 0.20f
#define MIDDLE_EXTENT 0.0f
#define BOTTOM_EXTENT -TOP_EXTENT
#define FRONT_EXTENT -1.25f
#define REAR_EXTENT -1.75f

#define GREEN_COLOR 0.75f, 0.75f, 1.0f, 1.0f
#define BLUE_COLOR 0.0f, 0.5f, 0.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f

    const float vertexData[] = {
        // Object 1 positions
        LEFT_EXTENT,
        TOP_EXTENT,
        REAR_EXTENT,
        LEFT_EXTENT,
        MIDDLE_EXTENT,
        FRONT_EXTENT,
        RIGHT_EXTENT,
        MIDDLE_EXTENT,
        FRONT_EXTENT,
        RIGHT_EXTENT,
        TOP_EXTENT,
        REAR_EXTENT,

        LEFT_EXTENT,
        BOTTOM_EXTENT,
        REAR_EXTENT,
        LEFT_EXTENT,
        MIDDLE_EXTENT,
        FRONT_EXTENT,
        RIGHT_EXTENT,
        MIDDLE_EXTENT,
        FRONT_EXTENT,
        RIGHT_EXTENT,
        BOTTOM_EXTENT,
        REAR_EXTENT,

        LEFT_EXTENT,
        TOP_EXTENT,
        REAR_EXTENT,
        LEFT_EXTENT,
        MIDDLE_EXTENT,
        FRONT_EXTENT,
        LEFT_EXTENT,
        BOTTOM_EXTENT,
        REAR_EXTENT,

        RIGHT_EXTENT,
        TOP_EXTENT,
        REAR_EXTENT,
        RIGHT_EXTENT,
        MIDDLE_EXTENT,
        FRONT_EXTENT,
        RIGHT_EXTENT,
        BOTTOM_EXTENT,
        REAR_EXTENT,

        LEFT_EXTENT,
        BOTTOM_EXTENT,
        REAR_EXTENT,
        LEFT_EXTENT,
        TOP_EXTENT,
        REAR_EXTENT,
        RIGHT_EXTENT,
        TOP_EXTENT,
        REAR_EXTENT,
        RIGHT_EXTENT,
        BOTTOM_EXTENT,
        REAR_EXTENT,

        //	0, 2, 1,
        //	3, 2, 0,

        // Object 2 positions
        TOP_EXTENT,
        RIGHT_EXTENT,
        REAR_EXTENT,
        MIDDLE_EXTENT,
        RIGHT_EXTENT,
        FRONT_EXTENT,
        MIDDLE_EXTENT,
        LEFT_EXTENT,
        FRONT_EXTENT,
        TOP_EXTENT,
        LEFT_EXTENT,
        REAR_EXTENT,

        BOTTOM_EXTENT,
        RIGHT_EXTENT,
        REAR_EXTENT,
        MIDDLE_EXTENT,
        RIGHT_EXTENT,
        FRONT_EXTENT,
        MIDDLE_EXTENT,
        LEFT_EXTENT,
        FRONT_EXTENT,
        BOTTOM_EXTENT,
        LEFT_EXTENT,
        REAR_EXTENT,

        TOP_EXTENT,
        RIGHT_EXTENT,
        REAR_EXTENT,
        MIDDLE_EXTENT,
        RIGHT_EXTENT,
        FRONT_EXTENT,
        BOTTOM_EXTENT,
        RIGHT_EXTENT,
        REAR_EXTENT,

        TOP_EXTENT,
        LEFT_EXTENT,
        REAR_EXTENT,
        MIDDLE_EXTENT,
        LEFT_EXTENT,
        FRONT_EXTENT,
        BOTTOM_EXTENT,
        LEFT_EXTENT,
        REAR_EXTENT,

        BOTTOM_EXTENT,
        RIGHT_EXTENT,
        REAR_EXTENT,
        TOP_EXTENT,
        RIGHT_EXTENT,
        REAR_EXTENT,
        TOP_EXTENT,
        LEFT_EXTENT,
        REAR_EXTENT,
        BOTTOM_EXTENT,
        LEFT_EXTENT,
        REAR_EXTENT,

        // Object 1 colors
        GREEN_COLOR,
        GREEN_COLOR,
        GREEN_COLOR,
        GREEN_COLOR,

        BLUE_COLOR,
        BLUE_COLOR,
        BLUE_COLOR,
        BLUE_COLOR,

        RED_COLOR,
        RED_COLOR,
        RED_COLOR,

        GREY_COLOR,
        GREY_COLOR,
        GREY_COLOR,

        BROWN_COLOR,
        BROWN_COLOR,
        BROWN_COLOR,
        BROWN_COLOR,

        // Object 2 colors
        RED_COLOR,
        RED_COLOR,
        RED_COLOR,
        RED_COLOR,

        BROWN_COLOR,
        BROWN_COLOR,
        BROWN_COLOR,
        BROWN_COLOR,

        BLUE_COLOR,
        BLUE_COLOR,
        BLUE_COLOR,

        GREEN_COLOR,
        GREEN_COLOR,
        GREEN_COLOR,

        GREY_COLOR,
        GREY_COLOR,
        GREY_COLOR,
        GREY_COLOR,
    };

    const ushort indexData[] =
        {
            0,
            2,
            1,
            3,
            2,
            0,

            4,
            5,
            6,
            6,
            7,
            4,

            8,
            9,
            10,
            11,
            13,
            12,

            14,
            16,
            15,
            17,
            16,
            14,
        };
#pragma endregion Test Data

    auto vb = ctx->CreateVertexBuffer(sizeof(vertexData));
    vb->SetData(vertexData, sizeof(vertexData));
    vb->SetLayout(
        BufferLayout(
            sizeof(vertexData),
            {{ShaderDataType::Float3, "position"}, {ShaderDataType::Float4, "color"}},
            BufferLayoutType::Contiguous));
    auto ib = ctx->CreateIndexBuffer(indexData, ARRAY_COUNT(indexData));

    auto va = ctx->CreateVertexArray();
    va->AddVertexBuffer(vb);
    va->SetIndexBuffer(ib);

    auto shader = ctx->CreateShader();
    shader->Load(ShaderType::Vertex, "shader.vert");
    shader->Load(ShaderType::Fragment, "shader.frag");
    shader->Link();
    shader->Bind();

    // TODO: move glm methods to Maths.h
    Mat4 proj = glm::perspective(glm::radians(90.0f), ((float)window->GetWidth() / (float)window->GetHeight()), 0.1f, 10.0f);

    shader->SetUniform("perspectiveMatrix", proj);

    float totalTimeElapsedInMs = 0;
    while (IsRunning)
    {
      PerformanceTimer frameTimer("Frame");
      int64 startCounter = Performance::GetTicks();

      window->BeginFrame();
      input->BeginFrame();
      {
        ctx->Clear(ClearFlags::Color | ClearFlags::Depth);

        shader->SetUniform("offset", Vec3(0.0f, 0.0f, 0.0f));
        glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);

        shader->SetUniform("offset", offset);
        glDrawElementsBaseVertex(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0, numberOfVertices / 2);
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