#pragma once

#include "Core/Events/Event.hpp"
#include "Core/Input/Buttons.hpp"

namespace Krys
{
  /// @brief Represents a mouse button interaction.
  class MouseButtonEvent : public Event
  {
  public:
    KRYS_EVENT_CLASS_TYPE("mouse-button-event")

    /// @brief Constructs a `MouseButtonEvent`.
    /// @param button The mouse button involved in the interaction.
    /// @param state The button's state during the interaction.
    MouseButtonEvent(const MouseButton button, const MouseButtonState state) noexcept;

    /// @brief Gets the mouse button involved in the interaction.
    NO_DISCARD MouseButton GetButton() const noexcept;

    /// @brief Gets the state of the mouse button.
    NO_DISCARD MouseButtonState GetState() const noexcept;

    /// @brief Checks if the button is pressed.
    /// @returns `true` if the button is in the state `MouseButtonState::Pressed`.
    NO_DISCARD bool IsPressed() const noexcept;

    /// @brief Checks if the button was released.
    /// @returns `true` if the button is in the state `MouseButtonState::Released`.
    NO_DISCARD bool WasReleased() const noexcept;

  private:
    MouseButton _button;
    MouseButtonState _state;
  };
}