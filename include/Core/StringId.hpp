#pragma once

#include "Core/Types.hpp"

namespace Krys
{
  /// @brief FNV-1a 32bit hashing algorithm.
  constexpr uint32 fnv1a_32(char const *s, size_t count)
  {
    return ((count ? fnv1a_32(s, count - 1) : 2'166'136'261u) ^ s[count]) * 16'777'619u;
  }

  constexpr uint32 operator""_sid(char const *s, size_t count)
  {
    return fnv1a_32(s, count);
  }

  class StringId
  {
  private:
    uint32 _hash;

  public:
    constexpr StringId(uint32 hash) noexcept;
    constexpr bool operator==(const StringId &other) const noexcept;
    constexpr bool operator!=(const StringId &other) const noexcept;
    constexpr operator uint32() const noexcept;
  };

  struct StringIdHasher
  {
    size_t operator()(const StringId &sid) const noexcept
    {
      return static_cast<size_t>(static_cast<uint32>(sid));
    }
  };

#define SID(x) Krys::StringId(x##_sid)
}