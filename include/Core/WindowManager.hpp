#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Core/ApplicationSettings.hpp"
#include "Core/Window.hpp"

namespace Krys
{
  class EventManager;
  class InputManager;

  /// @brief Handles the creation and management of a `Window`.
  class WindowManager
  {
  public:
    /// @brief Constructs a `WindowManager`.
    /// @param eventManager A pointer to the current `EventManager`.
    /// @param inputManager A pointer to the current `InputManager`.
    WindowManager(Ptr<EventManager> eventManager, Ptr<InputManager> inputManager) noexcept;

    virtual ~WindowManager() = default;

    /// @brief Get a pointer to the current window.
    Ptr<Window> GetCurrentWindow() const noexcept;

    /// @brief Create a new `Window` with the desired properties.
    /// @param settings The settings to use when creating the window.
    virtual Ptr<Window> Create(const ApplicationSettings &settings) noexcept = 0;

  protected:
    Ptr<EventManager> _eventManager;
    Ptr<InputManager> _inputManager;
    Unique<Window> _currentWindow;
  };
}