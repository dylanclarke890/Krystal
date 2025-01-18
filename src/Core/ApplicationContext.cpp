#include "Core/ApplicationContext.hpp"

namespace Krys
{
  ApplicationContext::ApplicationContext(int argc, char **argv, const ApplicationSettings &settings) noexcept
      : _settings(settings), _args(argc)
  {
    std::transform(argv, argv + argc, std::begin(_args), [](const char *arg) -> string { return arg; });
  }

  Ptr<EventManager> ApplicationContext::GetEventManager() const noexcept
  {
    return _eventManager.get();
  }

  Ptr<WindowManager> ApplicationContext::GetWindowManager() const noexcept
  {
    return _windowManager.get();
  }

  Ptr<InputManager> ApplicationContext::GetInputManager() const noexcept
  {
    return _inputManager.get();
  }

  Ptr<Gfx::Renderer> ApplicationContext::GetRenderer() const noexcept
  {
    return _renderer.get();
  }

  Ptr<Gfx::GraphicsContext> ApplicationContext::GetGraphicsContext() const noexcept
  {
    return _graphicsContext.get();
  }

  const ApplicationSettings &ApplicationContext::GetSettings() const noexcept
  {
    return _settings;
  }

  const List<string> &ApplicationContext::GetCLIArgs() const noexcept
  {
    return _args;
  }
}
