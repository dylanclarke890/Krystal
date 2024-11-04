#include "Core/Window.hpp"

namespace Krys
{
  Window::Window(uint32 width, uint32 height, EventManager *eventManager) noexcept
      : _width(width), _height(height), _eventManager(eventManager)
  {
  }

  NO_DISCARD uint32 Window::Width() const noexcept
  {
    return _width;
  }

  NO_DISCARD uint32 Window::Height() const noexcept
  {
    return _height;
  }
}
