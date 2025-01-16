#pragma once

#include "Platform/Win32/Win32Window.hpp"
#include "Core/ApplicationSettings.hpp"

namespace Krys::Platform
{
  class Win32OpenGLWindow : public Win32Window
  {
  public:
    Win32OpenGLWindow(const ApplicationSettings& settings, Ptr<EventManager> eventManager,
                      Ptr<InputManager> inputManager) noexcept;
    ~Win32OpenGLWindow() noexcept override = default;

    void SetVSync(bool enabled) noexcept override;

  private:
    void InitOpenGLExtensions(HINSTANCE instance) const noexcept;
  };
}