#include "Core/Window.hpp"

namespace Krys
{
  Window::Window(uint32 width, uint32 height, float fps, Ptr<EventManager> eventManager,
                 Ptr<InputManager> inputManager) noexcept
      : _width(width), _height(height), _fps(fps), _eventManager(eventManager), _inputManager(inputManager)
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

  NO_DISCARD bool Window::VSync() const noexcept
  {
    return _vsyncEnabled;
  }

  NO_DISCARD float Window::Fps() const noexcept
  {
    return _fps;
  }

  void Window::SetFps(float fps) noexcept
  {
    _fps = fps;
  }
}
