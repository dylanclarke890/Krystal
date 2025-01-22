#include "Core/Application.hpp"
#include "Core/ApplicationContext.hpp"
#include "Core/Events/EventManager.hpp"
#include "Core/Platform.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/OpenGL/OpenGLMeshManager.hpp"
#include "Graphics/OpenGL/OpenGLTextureManager.hpp"
#include "Graphics/Renderer.hpp"
#include "Platform/Win32/Input/Win32InputManager.hpp"
#include "Platform/Win32/Win32WindowManager.hpp"

namespace Krys
{
  Unique<ApplicationContext>
    Application::CreateApplicationContext(int argc, char **argv, const ApplicationSettings &settings) noexcept
  {
    Platform::Initialize();

    auto ctx = CreateUnique<ApplicationContext>(argc, argv, settings);
    ctx->_eventManager = CreateUnique<EventManager>();
    {
      using namespace Platform;
      ctx->_inputManager = CreateUnique<Win32InputManager>(ctx->_eventManager.get());
      ctx->_windowManager =
        CreateUnique<Win32WindowManager>(ctx->_eventManager.get(), ctx->_inputManager.get());
    }
    {
      using namespace Gfx::OpenGL;
      ctx->_graphicsContext = CreateUnique<OpenGLGraphicsContext>();
      ctx->_meshManager = CreateUnique<OpenGLMeshManager>(ctx->_graphicsContext.get());
      ctx->_renderer = CreateUnique<Gfx::Renderer>(ctx->_meshManager.get());
      ctx->_textureManager = CreateUnique<OpenGLTextureManager>();
    }
    return ctx;
  }
}