#include "Core/WindowManager.hpp"
#include "Core/Window.hpp"

namespace Krys
{
  WindowManager::WindowManager(EventManager *eventManager) noexcept
      : _eventManager(eventManager), _currentWindow(nullptr)
  {
  }

  Window *WindowManager::GetCurrentWindow() const noexcept
  {
    return _currentWindow.get();
  }
}
