#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"

#include <cmath>

namespace Krys::MTL
{
  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsNaN(TFloat a) noexcept
  {
    return std::isnan(a);
  }

  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsFinite(TFloat a) noexcept
  {
    return std::isfinite(a);
  }

  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsInf(TFloat a) noexcept
  {
    return std::isinf(a);
  }

  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsNormal(TFloat a) noexcept
  {
    return std::isnormal(a);
  }

  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD bool IsDenormal(TFloat a) noexcept
  {
    return std::fpclassify(x) == FP_SUBNORMAL;
  }

#pragma region Min

  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Min(TNumber a, TNumber b) noexcept
  {
    return a < b ? a : b;
  }

  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Min(TNumber a, TNumber b, TNumber c) noexcept
  {
    return MTL::Min(MTL::Min(a, b), c);
  }

  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Min(TNumber a, TNumber b, TNumber c, TNumber d) noexcept
  {
    return MTL::Min(MTL::Min(a, b), MTL::Min(c, d));
  }

#pragma endregion Min

#pragma region FMin

  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD TFloat FMin(TFloat a, TFloat b) noexcept
  {
    if (MTL::IsNaN(a))
      return b;
    return MTL::Min(a, b);
  }

  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber FMin(TNumber a, TNumber b, TNumber c) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMin(b, c);
    if (MTL::IsNaN(b))
      return MTL::FMin(a, c);
    if (MTL::IsNaN(c))
      return MTL::Min(a, b);
    return MTL::Min(a, b, c);
  }

  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber FMin(TNumber a, TNumber b, TNumber c, TNumber d) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMin(b, c, d);
    if (MTL::IsNaN(b))
      return MTL::Min(a, MTL::FMin(c, d));
    if (MTL::IsNaN(c))
      return MTL::FMin(MTL::Min(a, b), d);
    if (MTL::IsNaN(d))
      return MTL::Min(a, b, c);
    return MTL::Min(a, b, c, d);
  }

#pragma endregion FMin

#pragma region Max

  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Max(TNumber a, TNumber b) noexcept
  {
    return a > b ? a : b;
  }

  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Max(TNumber a, TNumber b, TNumber c) noexcept
  {
    return MTL::Max(MTL::Max(a, b), c);
  }

  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Max(TNumber a, TNumber b, TNumber c, TNumber d) noexcept
  {
    return MTL::Max(MTL::Max(a, b), MTL::Max(c, d));
  }

#pragma endregion Max

#pragma region FMax

  template <IsFloatingPointT TFloat>
  constexpr NO_DISCARD TFloat FMax(TFloat a, TFloat b) noexcept
  {
    if (MTL::IsNaN(a))
      return b;
    return MTL::Max(a, b);
  }

  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber FMax(TNumber a, TNumber b, TNumber c) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMax(b, c);
    if (MTL::IsNaN(b))
      return MTL::FMax(a, c);
    if (MTL::IsNaN(c))
      return MTL::Max(a, b);
    return MTL::Max(a, b, c);
  }

  template <IsFloatingPointT TNumber>
  constexpr NO_DISCARD TNumber FMax(TNumber a, TNumber b, TNumber c, TNumber d) noexcept
  {
    if (MTL::IsNaN(a))
      return MTL::FMax(b, c, d);
    if (MTL::IsNaN(b))
      return MTL::Max(a, MTL::FMax(c, d));
    if (MTL::IsNaN(c))
      return MTL::FMax(MTL::Max(a, b), d);
    if (MTL::IsNaN(d))
      return MTL::Max(a, b, c);
    return MTL::Max(a, b, c, d);
  }

#pragma endregion FMax

  template <IsArithmeticT TNumber>
  constexpr NO_DISCARD TNumber Clamp(TNumber value, TNumber min, TNumber max) noexcept
  {
    return Min<TNumber>(Max<TNumber>(value, min), max);
  }
}