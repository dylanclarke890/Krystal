#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/ApplicationSettings.hpp"
#include "Core/Events/EventManager.hpp"
#include "Core/Input/InputManager.hpp"
#include "Core/WindowManager.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/Renderer.hpp"

namespace Krys
{
  class Application;

  class ApplicationContext
  {
    friend class Application;

  public:
    NO_COPY_AND_ASSIGN(ApplicationContext)

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
    ApplicationSettings _settings;

    /// @brief Program arguments.
    List<string> _args;
  };
}