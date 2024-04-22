#pragma once

#include <glad.h>
#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Krystal.h"
#include "Application.h"
#include "Input/MouseButtons.h"
#include "Input/KeyCodes.h"
#include "Misc/Performance.h"
#include "Misc/Chrono.h"

#define ARRAY_COUNT(data) (sizeof(data) / sizeof(data[0]))

namespace Krys
{
  static GLuint LoadShaders(const char *vertexFile, const char *fragmentFile)
  {
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertexFile, std::ios::in);
    if (VertexShaderStream.is_open())
    {
      std::stringstream sstr;
      sstr << VertexShaderStream.rdbuf();
      VertexShaderCode = sstr.str();
      VertexShaderStream.close();
    }
    else
    {
      KRYS_ASSERT(false, "Unable to open %s. Are you in the right directory?", vertexFile);
      return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragmentFile, std::ios::in);
    if (FragmentShaderStream.is_open())
    {
      std::stringstream sstr;
      sstr << FragmentShaderStream.rdbuf();
      FragmentShaderCode = sstr.str();
      FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    KRYS_INFO("Compiling shader : %s", vertexFile);
    char const *VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
      std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
      glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      KRYS_ERROR("%s", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    KRYS_INFO("Compiling shader : %s", fragmentFile);
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
      std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
      glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
      KRYS_ERROR("%s", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    KRYS_INFO("Linking program");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
      std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
      glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
      KRYS_ERROR("%s", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
  }

  static void ComputePositionOffsets(float elapsed, float &xOffset, float &yOffset)
  {
    const float loopDuration = 1000.0f;
    const float scale = 3.14159f * 2.0f / loopDuration;

    float currTimeThroughLoop = fmodf(elapsed, loopDuration);

    xOffset = cosf(currTimeThroughLoop * scale) * 0.5f;
    yOffset = sinf(currTimeThroughLoop * scale) * 0.5f;
  }

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
        0.5f,
        -0.366f,
        0.0f,
        1.0f,
        -0.5f,
        -0.366f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
    };

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STREAM_DRAW);

    GLuint programID = LoadShaders("shader.vert", "shader.frag");

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float totalTimeElapsed = 0;
    while (IsRunning)
    {
      int64 startCounter = Performance::GetTicks();

      window->BeginFrame();
      input->BeginFrame();
      {
        float xOffset = 0.0f, yOffset = 0.0f;
        ComputePositionOffsets(totalTimeElapsed, xOffset, yOffset);
        std::vector<float> newData(ARRAY_COUNT(vertexData));
        memcpy(&newData[0], vertexData, sizeof(vertexData));

        for (int iVertex = 0; iVertex < ARRAY_COUNT(vertexData); iVertex += 4)
        {
          newData[iVertex] += xOffset;
          newData[iVertex + 1] += yOffset;
        }

        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexData), &newData[0]);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)48);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glUseProgram(programID);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
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

      totalTimeElapsed += elapsedMs;

      KRYS_INFO("Frame time: %.02f ms.", elapsedMs);
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