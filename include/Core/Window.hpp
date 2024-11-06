#pragma once

#include "Core/Attributes.hpp"
#include "Core/Pointers.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class EventManager;
  class InputManager;

  class Window
  {
  public:
    NO_COPY_AND_ASSIGN(Window)

    virtual ~Window() noexcept = default;

    NO_DISCARD uint32 Width() const noexcept;
    NO_DISCARD uint32 Height() const noexcept;

    virtual void Poll() noexcept = 0;

  protected:
    Window(uint32 width, uint32 height, Ptr<EventManager> eventManager, Ptr<InputManager> inputManager) noexcept;

  protected:
    uint32 _width, _height;
    Ptr<EventManager> _eventManager;
    Ptr<InputManager> _inputManager;
  };
}