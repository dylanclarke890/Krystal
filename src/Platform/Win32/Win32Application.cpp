#include "Core/Application.hpp"
#include "Core/ApplicationContext.hpp"
#include "Core/Events/EventManager.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/OpenGL/OpenGLRenderer.hpp"
#include "Platform/Win32/Input/Win32InputManager.hpp"
#include "Platform/Win32/Win32WindowManager.hpp"

namespace Krys
{
  Unique<ApplicationContext>
    Application::CreateApplicationContext(int argc, char **argv, const ApplicationSettings &settings) noexcept
  {
    auto ctx = CreateUnique<ApplicationContext>(argc, argv, settings);

    ctx->_eventManager = CreateUnique<EventManager>();
    {
      using namespace Platform;
      ctx->_inputManager = CreateUnique<Win32InputManager>(ctx->_eventManager.get());
      ctx->_windowManager =
        CreateUnique<Win32WindowManager>(ctx->_eventManager.get(), ctx->_inputManager.get());
    }
    {
      using namespace Graphics::OpenGL;
      ctx->_graphicsContext = CreateUnique<OpenGLGraphicsContext>();
      ctx->_renderer = CreateUnique<OpenGLRenderer>(ctx->_graphicsContext.get());
    }
    return ctx;
  }
}