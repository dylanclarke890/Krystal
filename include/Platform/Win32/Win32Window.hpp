#pragma once

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "Base/Pointers.hpp"
#include "Core/ApplicationSettings.hpp"
#include "Core/Window.hpp"
#include "IO/Input/Keys.hpp"

namespace Krys::Platform
{
  class Win32Window : public Window
  {
  public:
    Win32Window(const ApplicationSettings& settings, Ptr<EventManager> eventManager,
                Ptr<InputManager> inputManager) noexcept;
    virtual ~Win32Window() noexcept override = default;

    void Poll() noexcept override;

    virtual void SetVSync(bool show) noexcept override = 0;

    void SwapBuffers() noexcept override;

    void Show(bool show) noexcept override;

    void ShowCursor(bool show) noexcept override;

    void LockCursor(bool lock) noexcept override;

    void SetTitle(const string &title) noexcept override;

    NO_DISCARD HDC GetDeviceContext() const noexcept;
    NO_DISCARD HWND GetWindowHandle() const noexcept;

  protected:
    static LRESULT CALLBACK StaticWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

    LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

    static string GetLastErrorAsString() noexcept;

  protected:
    HDC _deviceContext;
    HWND _windowHandle;
  };
}