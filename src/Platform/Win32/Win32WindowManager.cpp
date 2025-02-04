#include "Platform/Win32/Win32WindowManager.hpp"
#include "Debug/Macros.hpp"
#include "Events/EventManager.hpp"
#include "Platform/Win32/Win32OpenGLWindow.hpp"

namespace Krys::Platform
{
  Win32WindowManager::Win32WindowManager(Ptr<EventManager> eventManager,
                                         Ptr<InputManager> inputManager) noexcept
      : WindowManager(eventManager, inputManager)
  {
  }

  Ptr<Window> Win32WindowManager::Create(const ApplicationSettings &settings) noexcept
  {
    KRYS_ASSERT(!_currentWindow, "Already created a window");
    _currentWindow = CreateUnique<Win32OpenGLWindow>(settings, _eventManager, _inputManager);
    return _currentWindow.get();
  }
}
