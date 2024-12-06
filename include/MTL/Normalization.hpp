#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "MTL/Common/MinMax.hpp"
#include "MTL/Common/Rounding.hpp"

#include <algorithm>
#include <cmath>

namespace Krys::MTL
{
  NO_DISCARD constexpr inline float SignedByteToFloat(int8 c) noexcept
  {
    return Max(static_cast<float>(c) / 127.0f, -1.0f);
  }

  NO_DISCARD constexpr inline float UnsignedByteToFloat(uint8 c) noexcept
  {
    return static_cast<float>(c) / 255.0f;
  }

  NO_DISCARD constexpr inline float SignedShortToFloat(int16 c) noexcept
  {
    return Max(static_cast<float>(c) / 32767.0f, -1.0f);
  }

  NO_DISCARD constexpr inline float UnsignedShortToFloat(uint16 c) noexcept
  {
    return static_cast<float>(c) / 65535.0f;
  }

  NO_DISCARD constexpr inline int8 FloatToSignedByte(float f) noexcept
  {
    return static_cast<int8>(MTL::Round(MTL::Max(f, -1.0f) * 127.0f));
  }

  NO_DISCARD constexpr inline uint8 FloatToUnsignedByte(float f) noexcept
  {
    return static_cast<uint8>(MTL::Round(f * 255.0f));
  }

  NO_DISCARD constexpr inline int16 FloatToSignedShort(float f) noexcept
  {
    return static_cast<int16>(MTL::Round(MTL::Max(f, -1.0f) * 32767.0f));
  }

  NO_DISCARD constexpr inline uint16 FloatToUnsignedShort(float f) noexcept
  {
    return static_cast<uint16>(MTL::Round(f * 65535.0f));
  }
}
