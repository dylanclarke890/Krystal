#pragma once

#include "Platform/Win32/Win32Window.hpp"

namespace Krys::Platform
{
  class Win32OpenGLWindow : public Win32Window
  {
  public:
    Win32OpenGLWindow(uint32 width, uint32 height, EventManager *eventManager) noexcept;
    ~Win32OpenGLWindow() noexcept override = default;

  private:
    void InitOpenGLExtensions(HINSTANCE instance) const noexcept;
  };
}