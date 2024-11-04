#pragma once

#include "Core/Pointers.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class EventManager;
  class Window;

  class WindowManager
  {
  public:
    WindowManager(EventManager *eventManager) noexcept;
    virtual ~WindowManager() = default;

    Window *GetCurrentWindow() const noexcept;
    virtual Window const *Create(uint32 width, uint32 height) noexcept = 0;

  protected:
    EventManager *_eventManager;
    Unique<Window> _currentWindow;
  };
}