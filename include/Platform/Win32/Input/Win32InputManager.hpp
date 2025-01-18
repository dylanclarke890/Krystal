#pragma once

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "Core/Input/InputManager.hpp"
#include "Core/Input/Keys.hpp"

namespace Krys::Platform
{
  class Win32InputManager : public InputManager
  {
  public:
    Win32InputManager(Ptr<EventManager> eventManager) noexcept;
    
    bool HandleWindowsMessage(UINT message, WPARAM wParam, LPARAM lParam) noexcept;

    Key KeyCodeToEngineKey(const WPARAM keyCode) const noexcept;
  };
}