#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"

namespace Krys
{
  /// @brief FNV-1a 32bit hashing algorithm.
  NO_DISCARD constexpr uint32 fnv1a_32(char const *s, size_t count) noexcept
  {
    return ((count ? fnv1a_32(s, count - 1) : 2'166'136'261u) ^ s[count]) * 16'777'619u;
  }

  NO_DISCARD constexpr uint32 operator""_sid(char const *s, size_t count) noexcept
  {
    return fnv1a_32(s, count);
  }

  /// @brief Represent a hashed string. Strings are slow to compare, comparing hashed strings is much more
  /// efficient.
  class StringId
  {
  private:
    uint32 _hash;

  public:
    /// @brief Constructs a `StringId` with the given hash.
    /// @param hash The hashed string.
    explicit constexpr StringId(uint32 hash) noexcept : _hash(hash)
    {
    }

    /// @brief Constructs a `StringId` with the given string to hash.
    /// @param hash The string to hash.
    explicit constexpr StringId(string text) noexcept : _hash(fnv1a_32(text.c_str(), text.size()))
    {
    }

    NO_DISCARD constexpr bool operator==(const StringId &other) const noexcept
    {
      return _hash == other._hash;
    }

    NO_DISCARD constexpr bool operator!=(const StringId &other) const noexcept
    {
      return !(*this == other);
    }

    NO_DISCARD constexpr operator uint32() const noexcept
    {
      return _hash;
    }
  };

  /// @brief For use in Map<StringId, T, StringIdHasher>.
  struct StringIdHasher
  {
    size_t operator()(const StringId &sid) const noexcept
    {
      return static_cast<size_t>(static_cast<uint32>(sid));
    }
  };

#define SID(x) Krys::StringId(x##_sid)
}
