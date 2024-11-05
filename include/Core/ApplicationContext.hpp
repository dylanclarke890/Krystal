#pragma once

#include "Core/Attributes.hpp"
#include "Core/Events/EventManager.hpp"
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
    ApplicationContext(int argc, char **argv) noexcept;
    NO_COPY_AND_ASSIGN(ApplicationContext)

    EventManager *GetEventManager() const noexcept;
    WindowManager *GetWindowManager() const noexcept;

    const List<string> &GetArgs() const noexcept;

  private:
    Unique<EventManager> _eventManager;
    Unique<WindowManager> _windowManager;

    /// @brief Program arguments.
    List<string> _args;
  };
}