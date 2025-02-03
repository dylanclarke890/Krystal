#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/ApplicationSettings.hpp"
#include "Core/WindowManager.hpp"
#include "Events/EventManager.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/MeshManager.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/SceneManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "IO/Input/InputManager.hpp"

namespace Krys
{
  class Application;

  class ApplicationContext
  {
    friend class Application;

  public:
    NO_COPY(ApplicationContext)

    /// @brief Construct an `ApplicationContext`.
    /// @param argc Command line argument count.
    /// @param argv Command line arguments.
    ApplicationContext(int argc, char **argv, const ApplicationSettings &settings) noexcept;

    /// @brief Get the current `EventManager`.
    Ptr<EventManager> GetEventManager() const noexcept;

    /// @brief Get the current `WindowManager`.
    Ptr<WindowManager> GetWindowManager() const noexcept;

    /// @brief Get the current `InputManager`.
    Ptr<InputManager> GetInputManager() const noexcept;

    /// @brief Get the current `Renderer`.
    Ptr<Gfx::Renderer> GetRenderer() const noexcept;

    /// @brief Get the current `GraphicsContext`.
    Ptr<Gfx::GraphicsContext> GetGraphicsContext() const noexcept;

    /// @brief Get the current `MeshManager`.
    Ptr<Gfx::MeshManager> GetMeshManager() const noexcept;

    /// @brief Get the current `TextureManager`.
    Ptr<Gfx::TextureManager> GetTextureManager() const noexcept;

    /// @brief Get the current `MaterialManager`.
    Ptr<Gfx::MaterialManager> GetMaterialManager() const noexcept;

    /// @brief Get the current `SceneManager`.
    Ptr<Gfx::SceneManager> GetSceneManager() const noexcept;

    /// @brief Get the command line arguments.
    const List<string> &GetCLIArgs() const noexcept;

    /// @brief Get the application settings.
    const ApplicationSettings &GetSettings() const noexcept;

  private:
    Unique<EventManager> _eventManager;
    Unique<WindowManager> _windowManager;
    Unique<InputManager> _inputManager;
    Unique<Gfx::Renderer> _renderer;
    Unique<Gfx::GraphicsContext> _graphicsContext;
    Unique<Gfx::MeshManager> _meshManager;
    Unique<Gfx::TextureManager> _textureManager;
    Unique<Gfx::MaterialManager> _materialManager;
    Unique<Gfx::SceneManager> _sceneManager;
    ApplicationSettings _settings;

    /// @brief Program arguments.
    List<string> _args;
  };
}