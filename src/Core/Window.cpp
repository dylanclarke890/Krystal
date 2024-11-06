#include "Core/Window.hpp"

namespace Krys
{
  Window::Window(uint32 width, uint32 height, Ptr<EventManager> eventManager,
                 Ptr<InputManager> inputManager) noexcept
      : _width(width), _height(height), _eventManager(eventManager), _inputManager(inputManager)
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
