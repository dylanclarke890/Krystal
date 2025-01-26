#include "Core/Events/Input/MouseMoveEvent.hpp"

namespace Krys
{
  MouseMoveEvent::MouseMoveEvent(const float deltaX, const float deltaY, const float clientX,
                                 const float clientY) noexcept
      : Event(), _deltaX(deltaX), _deltaY(deltaY), _clientX(clientX), _clientY(clientY)
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

  NO_DISCARD float MouseMoveEvent::GetClientX() const noexcept
  {
    return _clientX;
  }

  NO_DISCARD float MouseMoveEvent::GetClientY() const noexcept
  {
    return _clientY;
  }
}
