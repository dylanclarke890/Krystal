#include "Core/Application.hpp"
#include "Core/ApplicationContext.hpp"
#include "Core/Events/EventManager.hpp"
#include "Platform/Win32/Input/Win32InputManager.hpp"
#include "Platform/Win32/Win32WindowManager.hpp"

namespace Krys
{
  Unique<ApplicationContext> Application::CreateApplicationContext(int argc, char **argv) noexcept
  {
    auto ctx = CreateUnique<ApplicationContext>(argc, argv);

    ctx->_eventManager = CreateUnique<EventManager>();
    ctx->_inputManager = CreateUnique<Win32InputManager>(ctx->_eventManager.get());
    ctx->_windowManager =
      CreateUnique<Platform::Win32WindowManager>(ctx->_eventManager.get(), ctx->_inputManager.get());

    return ctx;
  }
}