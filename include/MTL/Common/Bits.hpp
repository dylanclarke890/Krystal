#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

namespace Krys::MTL::Bits
{
  template <IsUnsignedT T>
  NO_DISCARD constexpr T Mask(T bits) noexcept
  {
    return bits >= sizeof(T) * 8 ? ~T(0) : (T(1) << bits) - 1;
  }

  template <IsUnsignedT T>
  NO_DISCARD constexpr T Set(T value, uint first, uint count) noexcept
  {
    return value | T(Mask(count) << first);
  }

  template <IsUnsignedT T>
  NO_DISCARD constexpr uint32 Count(T value) noexcept
  {
    uint count;
    for (count = 0; value; count++)
      value &= value - 1; // clear the least significant bit set
    return count;
  }

  template <IsUnsignedT T>
  NO_DISCARD constexpr T Unset(T value, uint first, uint count) noexcept
  {
    return value & ~T(Mask(count) << first);
  }

  template <IsIntegralT T>
  NO_DISCARD constexpr T RotateRight(T value, uint count) noexcept
  {
    const int size = sizeof(T) * 8;
    count %= size;
    return (value >> T(count)) | (value << T(size - count));
  }

  template <IsIntegralT T>
  NO_DISCARD constexpr T RotateLeft(T value, uint count) noexcept
  {
    const int size = sizeof(T) * 8;
    return (value << T(count)) | (value >> T(size - count));
  }
}