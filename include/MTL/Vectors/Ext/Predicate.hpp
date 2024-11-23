#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Checks if any of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The vector to check.
  /// @returns True if any of the components satified the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t L, IsPredicateCallableT<TComponent> TFunc>
  constexpr bool AnyOf(const vector_t<TComponent, L> &v, TFunc predicate) noexcept
  {
    if constexpr (L == 1)
      return predicate(v.x);
    else if constexpr (L == 2)
      return predicate(v.x) || predicate(v.y);
    else if constexpr (L == 3)
      return predicate(v.x) || predicate(v.y) || predicate(v.z);
    else if constexpr (L == 4)
      return predicate(v.x) || predicate(v.y) || predicate(v.z) || predicate(v.w);
    else
      static_assert(false, "Unsupported number of components.");
  }

  /// @brief Checks if all of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The vector to check.
  /// @returns True if all of the components satified the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t L, IsPredicateCallableT<TComponent> TFunc>
  constexpr bool AllOf(const vector_t<TComponent, L> &v, TFunc predicate) noexcept
  {
    if constexpr (L == 1)
      return predicate(v.x);
    else if constexpr (L == 2)
      return predicate(v.x) && predicate(v.y);
    else if constexpr (L == 3)
      return predicate(v.x) && predicate(v.y) && predicate(v.z);
    else if constexpr (L == 4)
      return predicate(v.x) && predicate(v.y) && predicate(v.z) && predicate(v.w);
    else
      static_assert(false, "Unsupported number of components.");
  }

  /// @brief Checks if none of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The vector to check.
  /// @returns True if none of the components satified the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t L, IsPredicateCallableT<TComponent> TFunc>
  constexpr bool NoneOf(const vector_t<TComponent, L> &v, TFunc predicate) noexcept
  {
    if constexpr (L == 1)
      return !predicate(v.x);
    else if constexpr (L == 2)
      return !predicate(v.x) && !predicate(v.y);
    else if constexpr (L == 3)
      return !predicate(v.x) && !predicate(v.y) && !predicate(v.z);
    else if constexpr (L == 4)
      return !predicate(v.x) && !predicate(v.y) && !predicate(v.z) && !predicate(v.w);
    else
      static_assert(false, "Unsupported number of components.");
  }
}