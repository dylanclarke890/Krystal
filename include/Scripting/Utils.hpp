#pragma once

#include "Base/Attributes.hpp"

namespace Krys::Scripting
{
  NO_DISCARD constexpr bool IsDigit(const char c) noexcept
  {
    return c >= '0' && c <= '9';
  }

  NO_DISCARD constexpr bool IsAlpha(const char c) noexcept
  {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  }

  NO_DISCARD constexpr bool IsAlphaNumeric(const char c) noexcept
  {
    return IsAlpha(c) || IsDigit(c);
  }

  NO_DISCARD constexpr bool IsIdentifierPrefix(const char c) noexcept
  {
    return IsAlpha(c) || c == '_';
  }

  NO_DISCARD constexpr bool IsIdentifier(const char c) noexcept
  {
    return IsAlphaNumeric(c) || c == '_';
  }
}