#pragma once

#include "Core/Attributes.hpp"
#include "Core/Events/Event.hpp"
#include "Core/Input/Keys.hpp"

namespace Krys
{
  class KeyboardEvent : public Event
  {
  public:
    KeyboardEvent(const Key key, const KeyState state) noexcept;

    KRYS_EVENT_CLASS_TYPE("keyboard-event")

    NO_DISCARD Key GetKey() const noexcept;
    NO_DISCARD KeyState GetState() const noexcept;

    NO_DISCARD bool IsPressed() const noexcept;
    NO_DISCARD bool WasReleased() const noexcept;

  private:
    Key _key;
    KeyState _state;
  };
}