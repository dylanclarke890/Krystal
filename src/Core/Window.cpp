#include "Core/Window.hpp"

namespace Krys
{
  Window::Window(const ApplicationSettings &settings, Ptr<EventManager> eventManager,
                 Ptr<InputManager> inputManager) noexcept
      : _width(settings.Width), _height(settings.Height), _vsyncEnabled(settings.VSync),
        _renderFrameRate(settings.RenderFrameRate), _title(settings.Title), _eventManager(eventManager),
        _inputManager(inputManager)
  {
  }

  NO_DISCARD uint32 Window::GetWidth() const noexcept
  {
    return _width;
  }

  NO_DISCARD uint32 Window::GetHeight() const noexcept
  {
    return _height;
  }

  NO_DISCARD const string &Window::GetTitle() const noexcept
  {
    return _title;
  }

  NO_DISCARD bool Window::IsVSyncEnabled() const noexcept
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
