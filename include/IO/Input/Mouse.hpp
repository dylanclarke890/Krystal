#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "IO/Input/Buttons.hpp"

namespace Krys
{
  class InputManager;

  /// @brief Manages the state of mouse input for the current frame.
  ///
  /// The `Mouse` class provides methods to query the state of mouse buttons and movement,
  /// including whether a button was pressed or released during the current frame. The mouse
  /// state is updated each frame by the `InputManager`, allowing for accurate per-frame input handling.
  class Mouse
  {
    friend class InputManager; // To allow the `InputManager` to directly update the state of the mouse.

  public:
    /// @brief Constructs a `Mouse`.
    Mouse() noexcept = default;

    /// @brief Gets the x-coordinate of the cursor in client space.
    /// @note The origin is the top-left corner of the window, minus the title bar.
    NO_DISCARD float GetClientX() const noexcept;

    /// @brief Gets the y-coordinate of the cursor in client space.
    /// @note The origin is the top-left corner of the window, minus the title bar.
    NO_DISCARD float GetClientY() const noexcept;

    /// @brief Gets the amount the cursor has moved along the x-axis since the last frame.
    NO_DISCARD float DeltaX() const noexcept;

    /// @brief Gets the amount the cursor has moved along the y-axis since the last frame.
    NO_DISCARD float DeltaY() const noexcept;

    /// @brief Checks if a button was pressed this frame.
    /// @param button The button to check.
    /// @returns `true` if the button is in the state `MouseButtonState::Pressed`.
    NO_DISCARD bool IsButtonPressed(MouseButton button) const noexcept;

    /// @brief Checks if a button is currently held down.
    /// @param button The button to check.
    /// @returns `true` if the button is in the state `MouseButtonState::Held`.
    NO_DISCARD bool IsButtonHeld(MouseButton button) const noexcept;

    /// @brief Checks if a button was released this frame.
    /// @param button The button to check.
    /// @returns `true` if the button is in the state `MouseButtonState::Pressed`.
    NO_DISCARD bool WasButtonReleased(MouseButton button) const noexcept;

  private:
    float _clientX {0}, _clientY {0};
    float _deltaX {0}, _deltaY {0};
    MouseButton _pressed {MouseButton::None}, _released {MouseButton::None}, _held {MouseButton::None};
  };
}
