#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"

namespace Krys
{
  template <ArithmeticType T>
  struct BoundingBox
  {
    T Left, Right, Bottom, Top;

    constexpr BoundingBox() noexcept : Left(T(0)), Right(T(0)), Bottom(T(0)), Top(T(0))
    {
    }

    constexpr BoundingBox(T left, T right, T bottom, T top) noexcept
        : Left(left), Right(right), Bottom(bottom), Top(top)
    {
    }

    constexpr NO_DISCARD T GetWidth() const noexcept
    {
      return Right - Left;
    }

    constexpr NO_DISCARD T GetHeight() const noexcept
    {
      return Top - Bottom;
    }
  };
}