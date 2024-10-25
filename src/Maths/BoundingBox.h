#pragma once

#include "Core.h"

namespace Krys
{
  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
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