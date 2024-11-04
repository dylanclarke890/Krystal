#include "Core/StringId.hpp"

namespace Krys
{
  constexpr StringId::StringId(uint32 hash) noexcept : _hash(hash)
  {
  }

  constexpr bool StringId::operator==(const StringId &other) const noexcept
  {
    return _hash == other._hash;
  }

  constexpr bool StringId::operator!=(const StringId &other) const noexcept
  {
    return !(*this == other);
  }

  constexpr StringId::operator uint32() const noexcept
  {
    return _hash;
  }
}
