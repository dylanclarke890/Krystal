#pragma once

#include "Core/Attributes.hpp"
#include "Core/Input/Buttons.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class InputManager;

  class Mouse
  {
    friend class InputManager;

  public:
    Mouse() noexcept = default;

    NO_DISCARD float DeltaX() const noexcept;
    NO_DISCARD float DeltaY() const noexcept;

    NO_DISCARD bool IsButtonPressed(MouseButton button) const noexcept;
    NO_DISCARD bool WasButtonReleased(MouseButton button) const noexcept;

  private:
    float _deltaX, _deltaY;
    MouseButton _pressed, _released;
  };
}
