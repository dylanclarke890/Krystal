#pragma once

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "Core/Input/Keys.hpp"
#include "Core/Window.hpp"

namespace Krys::Platform
{
  class Win32Window : public Window
  {
  public:
    Win32Window(uint32 width, uint32 height, EventManager *eventManager) noexcept;
    virtual ~Win32Window() noexcept override = default;

    HDC GetDeviceContext() const noexcept;
    HWND GetWindowHandle() const noexcept;

  protected:
    static LRESULT CALLBACK StaticWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

    LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;
    Key KeyCodeToEngineKey(WPARAM keyCode) const noexcept;
    void ProcessWindowsMessages() const noexcept;

  protected:
    HDC _deviceContext;
    HWND _windowHandle;
  };
}