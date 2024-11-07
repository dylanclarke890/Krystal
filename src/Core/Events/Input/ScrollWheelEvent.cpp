#include "Core/Events/Input/ScrollWheelEvent.hpp"

namespace Krys
{
  ScrollWheelEvent::ScrollWheelEvent(const float delta) noexcept : Event(), _delta(delta)
  {
  }

  NO_DISCARD float ScrollWheelEvent::Delta() const noexcept
  {
    return _delta;
  }
}
