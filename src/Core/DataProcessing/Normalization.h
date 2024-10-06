#pragma once

#include "Core.h"
#include "Maths/Maths.h"
#include <algorithm>
#include <cmath>

namespace Krys::Normalization
{
  inline float FromSignedByteToFloat(int8 c) noexcept { return Max(c / 127.0f, -1.0f); }
  inline float FromUnsignedByteToFloat(uint8 c) noexcept { return c / 255.0f; }
  inline float FromSignedShortToFloat(int16 c) noexcept { return Max(c / 32767.0f, -1.0f); }
  inline float FromUnsignedShortToFloat(uint16 c) noexcept { return c / 65535.0f; }

  inline int8 ToSignedByte(float f) noexcept { return static_cast<int8>(std::round(Max(f, -1.0f) * 127.0f)); }
  inline uint8 ToUnsignedByte(float f) noexcept { return static_cast<uint8>(std::round(f * 255.0f)); }
  inline int16 ToSignedShort(float f) noexcept { return static_cast<int16>(std::round(Max(f, -1.0f) * 32767.0f)); }
  inline uint16 ToUnsignedShort(float f) noexcept { return static_cast<uint16>(std::round(f * 65535.0f)); }
}
