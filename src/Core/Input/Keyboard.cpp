#include "Core/Input/Keyboard.hpp"

namespace Krys
{
  NO_DISCARD bool Krys::Keyboard::IsKeyPressed(Key key) const noexcept
  {
    return _pressed.contains(key);
  }

  NO_DISCARD bool Krys::Keyboard::IsKeyHeld(Key key) const noexcept
  {
    return _held.contains(key);
  }

  NO_DISCARD bool Krys::Keyboard::WasKeyReleased(Key key) const noexcept
  {
    return _released.contains(key);
  }
}
