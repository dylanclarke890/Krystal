#include "Core/WindowManager.hpp"
#include "Core/Window.hpp"

namespace Krys
{
  WindowManager::WindowManager(Ptr<EventManager> eventManager, Ptr<InputManager> inputManager) noexcept
      : _eventManager(eventManager), _inputManager(inputManager), _currentWindow(nullptr)
  {
  }

  Ptr<Window> WindowManager::GetCurrentWindow() const noexcept
  {
    return _currentWindow.get();
  }
}
