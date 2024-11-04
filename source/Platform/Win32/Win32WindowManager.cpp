#include "Platform/Win32/Win32WindowManager.hpp"
#include "Core/Events/EventManager.hpp"
#include "Platform/Win32/Win32OpenGLWindow.hpp"

namespace Krys::Platform
{
  Win32WindowManager::Win32WindowManager(EventManager *eventManager) noexcept : WindowManager(eventManager)
  {
  }

  Window const *Win32WindowManager::Create(uint32 width, uint32 height) noexcept
  {
    // TODO: ensure window doesn't already exist.
    _currentWindow = CreateUnique<Win32OpenGLWindow>(width, height, _eventManager);
    return _currentWindow.get();
  }
}
