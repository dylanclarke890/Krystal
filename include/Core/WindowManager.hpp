#pragma once

#include "Core/Pointers.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class EventManager;
  class InputManager;
  class Window;

  class WindowManager
  {
  public:
    WindowManager(Ptr<EventManager> eventManager, Ptr<InputManager> inputManager) noexcept;
    virtual ~WindowManager() = default;

    Ptr<Window> GetCurrentWindow() const noexcept;
    virtual Ptr<Window> Create(uint32 width, uint32 height) noexcept = 0;

  protected:
    Ptr<EventManager> _eventManager;
    Ptr<InputManager> _inputManager;
    Unique<Window> _currentWindow;
  };
}