#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Vectors/Algorithms.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Rounds each component of the vector to the nearest integer. Halfway cases are rounded away from
  /// zero.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns A vector with each component rounded to the nearest integer.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Round(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Round(val); });
  }

  /// @brief Computes the largest integer not greater than each component of the vector.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns A vector with each component rounded down to the largest integer.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Floor(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Floor(val); });
  }

  /// @brief Computes the smallest integer not smaller than each component of the vector.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns A vector with each component rounded up to the smallest integer.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Ceil(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Ceil(val); });
  }

  /// @brief Computes the nearest integer not greater in magnitude than each component of the vector.
  /// @tparam TComponent The underlying floating-point type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns A vector with each component truncated to the nearest integer not greater in magnitude.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Trunc(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Trunc(val); });
  }
}
