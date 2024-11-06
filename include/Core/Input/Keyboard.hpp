#pragma once

#include "Core/Attributes.hpp"
#include "Core/Input/Keys.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class InputManager;

  class Keyboard
  {
    friend class InputManager;

  public:
    Keyboard() noexcept = default;

    NO_DISCARD bool IsKeyPressed(Key key) const noexcept;
    NO_DISCARD bool IsKeyHeld(Key key) const noexcept;
    NO_DISCARD bool WasKeyReleased(Key key) const noexcept;

  private:
    Set<Key> _pressed, _held, _released;
  };
}