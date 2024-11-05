#include "Core/ApplicationContext.hpp"

namespace Krys
{
  ApplicationContext::ApplicationContext(int argc, char **argv) noexcept : _args(argc)
  {
    std::transform(argv, argv + argc, std::begin(_args), [](const char *arg) -> string { return arg; });
  }

  EventManager *ApplicationContext::GetEventManager() const noexcept
  {
    return _eventManager.get();
  }

  WindowManager *ApplicationContext::GetWindowManager() const noexcept
  {
    return _windowManager.get();
  }

  const List<string> &ApplicationContext::GetArgs() const noexcept
  {
    return _args;
  }
}
