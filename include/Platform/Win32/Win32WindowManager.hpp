#pragma once

#include "Core/WindowManager.hpp"

namespace Krys::Platform
{
  class Win32WindowManager : public WindowManager
  {
  public:
    Win32WindowManager(EventManager *eventManager) noexcept;
    Window const *Create(uint32 width, uint32 height) noexcept override;
  };
}