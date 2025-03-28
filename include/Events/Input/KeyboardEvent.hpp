#pragma once

#include "Base/Attributes.hpp"
#include "Events/Event.hpp"
#include "IO/Input/Keys.hpp"

namespace Krys
{
  /// @brief Represents an interaction with a keyboard.
  class KeyboardEvent : public Event
  {
  public:
    KRYS_EVENT_CLASS_TYPE("keyboard-event")

    /// @brief Constructs a `KeyboardEvent`.
    /// @param button The key involved in the interaction.
    /// @param state The key's state during the interaction.
    KeyboardEvent(const Key key, const KeyState state) noexcept;

    /// @brief Gets the key involved in the interaction.
    NO_DISCARD Key GetKey() const noexcept;

    /// @brief Gets the state of the key.
    NO_DISCARD KeyState GetState() const noexcept;

  private:
    Key _key;
    KeyState _state;
  };
}