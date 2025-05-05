#include "Core/Application.hpp"
#include "Core/ApplicationContext.hpp"
#include "Core/Platform.hpp"
#include "Events/EventManager.hpp"
#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/OpenGL/OpenGLMeshManager.hpp"
#include "Graphics/OpenGL/OpenGLRenderer.hpp"
#include "Graphics/OpenGL/OpenGLTextureManager.hpp"
#include "Graphics/RenderContext.hpp"
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
      ctx->_lightManager = CreateUnique<Gfx::LightManager>();
      ctx->_graphicsContext = CreateUnique<OpenGLGraphicsContext>();
      ctx->_meshManager = CreateUnique<OpenGLMeshManager>(ctx->_graphicsContext.get());
      ctx->_textureManager = CreateUnique<OpenGLTextureManager>();
      ctx->_sceneGraphManager = CreateUnique<Gfx::SceneGraphManager>();
      ctx->_materialManager =
        CreateUnique<Gfx::MaterialManager>(ctx->_textureManager.get(), ctx->_graphicsContext.get());
      ctx->_modelManager = CreateUnique<Gfx::ModelManager>(
        ctx->_materialManager.get(), ctx->_meshManager.get(), ctx->_textureManager.get());
      ctx->_renderTargetManager =
        CreateUnique<Gfx::RenderTargetManager>(ctx->_windowManager.get(), ctx->_textureManager.get());

      Gfx::RenderContext renderContext {ctx->_graphicsContext.get(),     ctx->_meshManager.get(),
                                        ctx->_textureManager.get(),      ctx->_materialManager.get(),
                                        ctx->_lightManager.get(),        ctx->_sceneGraphManager.get(),
                                        ctx->_renderTargetManager.get(), ctx->_windowManager.get()};
      ctx->_renderer = CreateUnique<OpenGLRenderer>(renderContext);
      ctx->_fontManager = CreateUnique<Gfx::FontManager>(ctx->_textureManager.get());
    }
    return ctx;
  }
}