#pragma once

#include "Core/Pointers.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class EventManager;
  class InputManager;
  class Window;

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
    /// @param width The desired window width.
    /// @param height The desired window height.
    virtual Ptr<Window> Create(uint32 width, uint32 height) noexcept = 0;

  protected:
    Ptr<EventManager> _eventManager;
    Ptr<InputManager> _inputManager;
    Unique<Window> _currentWindow;
  };
}