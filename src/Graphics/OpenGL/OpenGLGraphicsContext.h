#pragma once

#include <windows.h>

#include "Krystal.h"
#include "GraphicsContext.h"

namespace Krys
{
  class OpenGLGraphicsContext : public GraphicsContext
  {
  private:
    HWND hWnd;
    HGLRC openGLContext;

  public:
    OpenGLGraphicsContext(HWND window) : hWnd(window), openGLContext(0) {}
    ~OpenGLGraphicsContext() override;

    void Init() override;
  };
}