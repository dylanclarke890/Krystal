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

  Ptr<Gfx::MeshManager> ApplicationContext::GetMeshManager() const noexcept
  {
    return _meshManager.get();
  }

  Ptr<Gfx::TextureManager> ApplicationContext::GetTextureManager() const noexcept
  {
    return _textureManager.get();
  }

  Ptr<Gfx::MaterialManager> ApplicationContext::GetMaterialManager() const noexcept
  {
    return _materialManager.get();
  }

  Ptr<Gfx::SceneGraphManager> ApplicationContext::GetSceneGraphManager() const noexcept
  {
    return _sceneGraphManager.get();
  }

  Ptr<Gfx::LightManager> ApplicationContext::GetLightManager() const noexcept
  {
    return _lightManager.get();
  }

  Ptr<Gfx::ModelManager> ApplicationContext::GetModelManager() const noexcept
  {
    return _modelManager.get();
  }

  Ptr<Gfx::RenderTargetManager> ApplicationContext::GetRenderTargetManager() const noexcept
  {
    return _renderTargetManager.get();
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
