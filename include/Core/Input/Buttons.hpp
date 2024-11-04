#pragma once

#include "Core/Types.hpp"

namespace Krys
{
  /// @brief Pressed or released.
  enum class MouseButtonState : uint8
  {
    Pressed,
    Released
  };

  /// @brief All possible mouse buttons.
  enum class MouseButton : uint16
  {
    UNKNOWN,
    LEFT = 0,
    RIGHT = 2,
    MIDDLE = 4,
    THUMB_1 = 8,
    THUMB_2 = 16
  };
}