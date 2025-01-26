#pragma once

#include "Base/Types.hpp"

namespace Krys::Gfx
{
  /// @brief Enumeration of possible light types.
  enum class LightType : uint8
  {
    Ambient,
    Directional,
    Point
  };
}