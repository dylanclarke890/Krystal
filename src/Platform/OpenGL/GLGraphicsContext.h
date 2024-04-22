#pragma once

#include <windows.h>

#include "Krystal.h"
#include "Graphics/GraphicsContext.h"

namespace Krys
{
  class GLGraphicsContext : public GraphicsContext
  {
  private:
    HWND hWnd;
    HDC dc;
    HGLRC openGLContext;

  public:
    GLGraphicsContext(HDC deviceContext, HWND window)
        : hWnd(window), dc(deviceContext), openGLContext(0) {}
    ~GLGraphicsContext() override;

    void Init() override;
    void Clear() override;
    void SetClearColor(float x, float y, float z, float a) override;
    void SetViewport(int width, int height) override;
  };
}