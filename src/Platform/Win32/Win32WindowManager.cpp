#include "Platform/Win32/Win32WindowManager.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Events/EventManager.hpp"
#include "Platform/Win32/Win32OpenGLWindow.hpp"

namespace Krys::Platform
{
  Win32WindowManager::Win32WindowManager(Ptr<EventManager> eventManager,
                                         Ptr<InputManager> inputManager) noexcept
      : WindowManager(eventManager, inputManager)
  {
  }

  Ptr<Window> Win32WindowManager::Create(uint32 width, uint32 height, float fps) noexcept
  {
    KRYS_ASSERT(!_currentWindow, "Already created a window", 0);
    _currentWindow = CreateUnique<Win32OpenGLWindow>(width, height, fps, _eventManager, _inputManager);
    return _currentWindow.get();
  }
}
