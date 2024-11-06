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

    ApplicationContext(int argc, char **argv) noexcept;

    Ptr<EventManager> GetEventManager() const noexcept;
    Ptr<WindowManager> GetWindowManager() const noexcept;
    Ptr<InputManager> GetInputManager() const noexcept;

    const List<string> &GetArgs() const noexcept;

  private:
    Unique<EventManager> _eventManager;
    Unique<WindowManager> _windowManager;
    Unique<InputManager> _inputManager;

    /// @brief Program arguments.
    List<string> _args;
  };
}