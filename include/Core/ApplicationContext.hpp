#pragma once

#include "Core/Attributes.hpp"
#include "Core/Events/EventManager.hpp"
#include "Core/Input/InputManager.hpp"
#include "Core/Pointers.hpp"
#include "Core/Types.hpp"
#include "Core/WindowManager.hpp"

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
    ApplicationContext(int argc, char **argv) noexcept;

    /// @brief Get the current `EventManager`.
    Ptr<EventManager> GetEventManager() const noexcept;

    /// @brief Get the current `WindowManager`.
    Ptr<WindowManager> GetWindowManager() const noexcept;

    /// @brief Get the current `InputManager`.
    Ptr<InputManager> GetInputManager() const noexcept;

    /// @brief Get the command line arguments.
    const List<string> &GetCLIArgs() const noexcept;

  private:
    Unique<EventManager> _eventManager;
    Unique<WindowManager> _windowManager;
    Unique<InputManager> _inputManager;

    /// @brief Program arguments.
    List<string> _args;
  };
}