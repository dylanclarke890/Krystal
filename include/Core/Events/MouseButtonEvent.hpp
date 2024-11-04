#pragma once

#include "Core/Events/Event.hpp"
#include "Core/Input/Buttons.hpp"

namespace Krys
{
  class MouseButtonEvent : public Event
  {
  public:
    MouseButtonEvent(const MouseButton button, const MouseButtonState state) noexcept;

    KRYS_EVENT_CLASS_TYPE("mouse-button-event")

    NO_DISCARD MouseButton GetButton() const noexcept;
    NO_DISCARD MouseButtonState GetState() const noexcept;

    NO_DISCARD bool IsPressed() const noexcept;
    NO_DISCARD bool WasReleased() const noexcept;

  private:
    MouseButton _button;
    MouseButtonState _state;
  };
}