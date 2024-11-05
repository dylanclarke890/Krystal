#include "Core/Events/MouseMoveEvent.hpp"

namespace Krys
{
  MouseMoveEvent::MouseMoveEvent(const float deltaX, const float deltaY) noexcept
      : Event(), _deltaX(deltaX), _deltaY(deltaY)
  {
  }

  NO_DISCARD float MouseMoveEvent::DeltaX() const noexcept
  {
    return _deltaX;
  }

  NO_DISCARD float MouseMoveEvent::DeltaY() const noexcept
  {
    return _deltaY;
  }
}
