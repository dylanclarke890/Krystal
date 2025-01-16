#include "Core/Window.hpp"

namespace Krys
{
  Window::Window(const ApplicationSettings &settings, Ptr<EventManager> eventManager,
                 Ptr<InputManager> inputManager) noexcept
      : _width(settings.Width), _height(settings.Height), _vsyncEnabled(settings.VSync),
        _renderFrameRate(settings.RenderFrameRate), _eventManager(eventManager), _inputManager(inputManager)
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

  NO_DISCARD float Window::GetRenderFrameRate() const noexcept
  {
    return _renderFrameRate;
  }

  void Window::SetRenderFrameRate(float newFrameRate) noexcept
  {
    _renderFrameRate = newFrameRate;
  }
}
