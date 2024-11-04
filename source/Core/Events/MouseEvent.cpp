#include "Core/Events/MouseEvent.hpp"

namespace Krys
{
  MouseEvent::MouseEvent(const float deltaX, const float deltaY) noexcept : _deltaX(deltaX), _deltaY(deltaY)
  {
  }

  NO_DISCARD float MouseEvent::DeltaX() const noexcept
  {
    return _deltaX;
  }

  NO_DISCARD float MouseEvent::DeltaY() const noexcept
  {
    return _deltaY;
  }
}
