#pragma once

#include "Core/Attributes.hpp"
#include "Core/Pointers.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class EventManager;

  class Window
  {
  public:
    Window(uint32 width, uint32 height, EventManager *eventManager) noexcept;
    virtual ~Window() noexcept = default;

    NO_COPY_AND_ASSIGN(Window)

    NO_DISCARD uint32 Width() const noexcept;
    NO_DISCARD uint32 Height() const noexcept;

  protected:
    uint32 _width, _height;
    EventManager *_eventManager;
  };
}