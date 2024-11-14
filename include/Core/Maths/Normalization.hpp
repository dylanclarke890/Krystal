#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Maths/Algorithms.hpp"

#include <algorithm>
#include <cmath>

namespace Krys::MTL
{
  constexpr inline NO_DISCARD float SignedByteToFloat(int8 c) noexcept
  {
    return Max(static_cast<float>(c) / 127.0f, -1.0f);
  }

  constexpr inline NO_DISCARD float UnsignedByteToFloat(uint8 c) noexcept
  {
    return static_cast<float>(c) / 255.0f;
  }

  constexpr inline NO_DISCARD float SignedShortToFloat(int16 c) noexcept
  {
    return Max(static_cast<float>(c) / 32767.0f, -1.0f);
  }

  constexpr inline NO_DISCARD float UnsignedShortToFloat(uint16 c) noexcept
  {
    return static_cast<float>(c) / 65535.0f;
  }

  constexpr inline NO_DISCARD int8 FloatToSignedByte(float f) noexcept
  {
    return static_cast<int8>(std::round(Max(f, -1.0f) * 127.0f));
  }

  constexpr inline NO_DISCARD uint8 FloatToUnsignedByte(float f) noexcept
  {
    return static_cast<uint8>(std::round(f * 255.0f));
  }

  constexpr inline NO_DISCARD int16 FloatToSignedShort(float f) noexcept
  {
    return static_cast<int16>(std::round(Max(f, -1.0f) * 32767.0f));
  }

  constexpr inline NO_DISCARD uint16 FloatToUnsignedShort(float f) noexcept
  {
    return static_cast<uint16>(std::round(f * 65535.0f));
  }
}
