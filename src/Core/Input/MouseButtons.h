#pragma once

#include "Core.h"

namespace Krys
{
  enum MouseButton
  {
    MouseButtonNone,
    Left = BIT(0),
    Right = BIT(1),
    Middle = BIT(2),
    Thumb1 = BIT(3),
    Thumb2 = BIT(4)
  };
}
