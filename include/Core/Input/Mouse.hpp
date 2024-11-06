#pragma once

#include "Core/Attributes.hpp"
#include "Core/Input/Buttons.hpp"
#include "Core/Types.hpp"

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
    friend class InputManager;

  public:
    /// @brief Constructs a `Mouse`.
    Mouse() noexcept = default;

    /// @brief Gets the amount the cursor has moved along the x-axis since the last frame.
    NO_DISCARD float DeltaX() const noexcept;

    /// @brief Gets the amount the cursor has moved along the y-axis since the last frame.
    NO_DISCARD float DeltaY() const noexcept;

    /// @brief Checks if a button was pressed this frame.
    /// @param button The button to check.
    /// @returns `true` if the button is in the state `MouseButtonState::Pressed`.
    NO_DISCARD bool IsButtonPressed(MouseButton button) const noexcept;

    /// @brief Checks if a button was released this frame.
    /// @param button The button to check.
    /// @returns `true` if the button is in the state `MouseButtonState::Pressed`.
    NO_DISCARD bool WasButtonReleased(MouseButton button) const noexcept;

  private:
    float _deltaX, _deltaY;
    MouseButton _pressed, _released;
  };
}
