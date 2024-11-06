#pragma once

#include "Core/WindowManager.hpp"

namespace Krys::Platform
{
  class Win32WindowManager : public WindowManager
  {
  public:
    Win32WindowManager(Ptr<EventManager> eventManager, Ptr<InputManager> inputManager) noexcept;

    Ptr<Window> Create(uint32 width, uint32 height) noexcept override;
  };
}