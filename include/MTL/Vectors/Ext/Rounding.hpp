#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Ceil.hpp"
#include "MTL/Common/Floor.hpp"
#include "MTL/Common/Round.hpp"
#include "MTL/Common/Trunc.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the smallest integer not smaller than each component of the vector.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param x The input vector.
  /// @returns An `L` size vector with each component rounded up to the smallest integer.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Ceil(vector_t<TComponent, L> x) noexcept
  {
    return MTL::MapEach(x, [](TComponent v) -> TComponent { return MTL::Ceil(v); });
  }

  /// @brief Computes the largest integer not greater than each component of the vector.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param x The input vector.
  /// @returns A `L` size vector with each component rounded down to the largest integer.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Floor(vector_t<TComponent, L> x) noexcept
  {
    return MTL::MapEach(x, [](TComponent v) -> TComponent { return MTL::Floor(v); });
  }

  /// @brief Round each component of the vector to the nearest integer.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param x The input vector.
  /// @note Halfway cases are rounded away from zero.
  /// @returns A vector with each component rounded to the nearest integer.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Round(vector_t<TComponent, L> x) noexcept
  {
    return MTL::MapEach(x, [](TComponent v) -> TComponent { return MTL::Round(v); });
  }

  /// @brief Computes the nearest integer not greater in magnitude than each component of the vector.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns A vector with each component truncated to the nearest integer not greater in magnitude.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Trunc(vector_t<TComponent, L> x) noexcept
  {
    return MTL::MapEach(x, [](TComponent v) -> TComponent { return MTL::Trunc(v); });
  }
}
