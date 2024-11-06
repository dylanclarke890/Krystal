#pragma once

#include "Core/Macros.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  /// @brief The state of a button during an interaction.
  enum class MouseButtonState : uint8
  {
    Pressed,
    Released
  };

  /// @brief Supported mouse buttons.
  enum class MouseButton : uint16
  {
    None = 0,
    LEFT = 1,
    RIGHT = 2,
    MIDDLE = 4,
    THUMB_1 = 8,
    THUMB_2 = 16,
    UNKNOWN = 32
  };

  ENUM_CLASS_BITWISE_OPERATORS(MouseButton, uint16)
}