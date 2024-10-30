#pragma once

#include "Core.h"

namespace Krys
{
  template <ArithmeticType T>
  struct BoundingBox
  {
    T Left, Right, Bottom, Top;

    BoundingBox() noexcept = default;
    constexpr BoundingBox(T left, T right, T bottom, T top) noexcept
        : Left(left), Right(right), Bottom(bottom), Top(top)
    {
    }

    constexpr T GetWidth() const noexcept
    {
      return Right - Left;
    }

    constexpr T GetHeight() const noexcept
    {
      return Top - Bottom;
    }
  };
}