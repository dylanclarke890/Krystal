#include "Events/Input/MouseButtonEvent.hpp"

namespace Krys
{
  MouseButtonEvent::MouseButtonEvent(const MouseButton button, const MouseButtonState state) noexcept
      : Event(), _button(button), _state(state)
  {
  }

  NO_DISCARD MouseButton MouseButtonEvent::GetButton() const noexcept
  {
    return _button;
  }

  NO_DISCARD MouseButtonState MouseButtonEvent::GetState() const noexcept
  {
    return _state;
  }

  NO_DISCARD bool MouseButtonEvent::IsPressed() const noexcept
  {
    return _state == MouseButtonState::Pressed;
  }

  NO_DISCARD bool MouseButtonEvent::WasReleased() const noexcept
  {
    return _state == MouseButtonState::Released;
  }
}
