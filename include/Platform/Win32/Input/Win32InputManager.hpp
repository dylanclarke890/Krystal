#pragma once

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "IO/Input/InputManager.hpp"
#include "IO/Input/Keys.hpp"

namespace Krys::Platform
{
  class Win32InputManager : public InputManager
  {
  public:
    Win32InputManager(Ptr<EventManager> eventManager) noexcept;
    
    bool HandleWindowsMessage(UINT message, WPARAM wParam, LPARAM lParam, HWND windowHandle) noexcept;

    Key KeyCodeToEngineKey(const WPARAM keyCode) const noexcept;
  };
}