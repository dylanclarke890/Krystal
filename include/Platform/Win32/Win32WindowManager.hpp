#pragma once

#include "Core/WindowManager.hpp"
#include "Core/ApplicationSettings.hpp"

namespace Krys::Platform
{
  class Win32WindowManager : public WindowManager
  {
  public:
    Win32WindowManager(Ptr<EventManager> eventManager, Ptr<InputManager> inputManager) noexcept;

    Ptr<Window> Create(const ApplicationSettings& settings) noexcept override;
  };
}