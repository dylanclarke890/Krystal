#include "IO/Input/Mouse.hpp"

namespace Krys
{
  NO_DISCARD float Mouse::GetClientX() const noexcept
  {
    return _clientX;
  }

  NO_DISCARD float Mouse::GetClientY() const noexcept
  {
    return _clientY;
  }

  NO_DISCARD float Mouse::DeltaX() const noexcept
  {
    return _deltaX;
  }

  NO_DISCARD float Mouse::DeltaY() const noexcept
  {
    return _deltaY;
  }

  NO_DISCARD bool Mouse::IsButtonPressed(MouseButton button) const noexcept
  {
    return (_pressed & button) == button;
  }

  NO_DISCARD bool Mouse::IsButtonHeld(MouseButton button) const noexcept
  {
    return (_held & button) == button;
  }

  NO_DISCARD bool Mouse::WasButtonReleased(MouseButton button) const noexcept
  {
    return (_released & button) == button;
  }
}
