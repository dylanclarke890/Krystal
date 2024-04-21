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
    HDC dc;
    HGLRC openGLContext;

  public:
    OpenGLGraphicsContext(HDC deviceContext, HWND window)
        : hWnd(window), dc(deviceContext), openGLContext(0) {}
    ~OpenGLGraphicsContext() override;

    void Init() override;
    void Clear() override;
    void SetClearColor(float x, float y, float z, float a) override;
    void OnResize(int width, int height) override;
    uint CreateTextureFromBMP(const char *imagePath) override;
  };
}