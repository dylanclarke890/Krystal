#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TNumber>
  struct BoundingBox
  {
    using dimension_t = TNumber;
    dimension_t Left, Right, Bottom, Top;

    constexpr BoundingBox() noexcept
        : Left(dimension_t(0)), Right(dimension_t(0)), Bottom(dimension_t(0)), Top(dimension_t(0))
    {
    }

    constexpr BoundingBox(dimension_t left, dimension_t right, dimension_t bottom, dimension_t top) noexcept
        : Left(left), Right(right), Bottom(bottom), Top(top)
    {
    }

    NO_DISCARD constexpr dimension_t GetWidth() const noexcept
    {
      return Right - Left;
    }

    NO_DISCARD constexpr dimension_t GetHeight() const noexcept
    {
      return Top - Bottom;
    }
  };
}