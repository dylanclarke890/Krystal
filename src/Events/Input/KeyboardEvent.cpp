#include "Events/Input/KeyboardEvent.hpp"

namespace Krys
{
  KeyboardEvent::KeyboardEvent(const Key key, const KeyState state) noexcept
      : Event(), _key(key), _state(state)
  {
  }

  NO_DISCARD Key KeyboardEvent::GetKey() const noexcept
  {
    return _key;
  }

  NO_DISCARD KeyState KeyboardEvent::GetState() const noexcept
  {
    return _state;
  }
}
