#pragma once

#include "Base/Types.hpp"

namespace Krys::Gfx
{
  /// @brief Enumeration of possible light types.
  enum class LightType : int
  {
    Point = 0,
    Directional = 1,
    Spot = 2
  };
}