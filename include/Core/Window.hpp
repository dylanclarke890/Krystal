#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"

namespace Krys
{
  class EventManager;
  class InputManager;

  /// @brief The window for the application. Provides various cross-platform functionality for managing a
  /// window.
  class Window
  {
  public:
    NO_COPY_AND_ASSIGN(Window)

    virtual ~Window() noexcept = default;

    /// @brief Get the width of the window.
    NO_DISCARD uint32 Width() const noexcept;

    /// @brief Get the height of the window.
    NO_DISCARD uint32 Height() const noexcept;

    /// @brief Polls the native window. Usually involves processing various OS events, some of which will
    /// result in an application event being raised.
    virtual void Poll() noexcept = 0;

  protected:
    /// @brief Constructs a `Window`.
    /// @param width The desired window width.
    /// @param height The desired window height.
    /// @param eventManager A pointer to the current `EventManager`.
    /// @param inputManager A pointer to the current `InputManager`.
    Window(uint32 width, uint32 height, Ptr<EventManager> eventManager, Ptr<InputManager> inputManager) noexcept;

  protected:
    uint32 _width, _height;
    Ptr<EventManager> _eventManager;
    Ptr<InputManager> _inputManager;
  };
}