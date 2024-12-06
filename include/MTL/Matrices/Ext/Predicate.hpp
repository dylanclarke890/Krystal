#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Matrices/Base.hpp"

namespace Krys::MTL
{
  /// @brief Checks if any of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @param v The matrix to check.
  /// @returns True if any of the components satisfied the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL,
            IsPredicateCallableT<TComponent> TFunc>
  constexpr bool AnyOf(const matrix_t<TComponent, RL, CL> &v, TFunc predicate) noexcept
  {
    if constexpr (RL == 2 && CL == 2)
      return predicate(v[0].x) || predicate(v[0].y) || predicate(v[1].x) || predicate(v[1].y);
    else if constexpr (RL == 3 && CL == 3)
      return predicate(v[0].x) || predicate(v[0].y) || predicate(v[0].z) || predicate(v[1].x)
             || predicate(v[1].y) || predicate(v[1].z) || predicate(v[2].x) || predicate(v[2].y)
             || predicate(v[2].z);
    else if constexpr (RL == 4 && CL == 4)
      return predicate(v[0].x) || predicate(v[0].y) || predicate(v[0].z) || predicate(v[0].w)
             || predicate(v[1].x) || predicate(v[1].y) || predicate(v[1].z) || predicate(v[1].w)
             || predicate(v[2].x) || predicate(v[2].y) || predicate(v[2].z) || predicate(v[2].w)
             || predicate(v[3].x) || predicate(v[3].y) || predicate(v[3].z) || predicate(v[3].w);
    else
      static_assert(false, "Unsupported number of components");
  }

  /// @brief Checks if all of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @param v The matrix to check.
  /// @returns True if all of the components satisfied the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL,
            IsPredicateCallableT<TComponent> TFunc>
  constexpr bool AllOf(const matrix_t<TComponent, RL, CL> &v, TFunc predicate) noexcept
  {
    if constexpr (RL == 2 && CL == 2)
      return predicate(v[0].x) && predicate(v[0].y) && predicate(v[1].x) && predicate(v[1].y);
    else if constexpr (RL == 3 && CL == 3)
      return predicate(v[0].x) && predicate(v[0].y) && predicate(v[0].z) && predicate(v[1].x)
             && predicate(v[1].y) && predicate(v[1].z) && predicate(v[2].x) && predicate(v[2].y)
             && predicate(v[2].z);
    else if constexpr (RL == 4 && CL == 4)
      return predicate(v[0].x) && predicate(v[0].y) && predicate(v[0].z) && predicate(v[0].w)
             && predicate(v[1].x) && predicate(v[1].y) && predicate(v[1].z) && predicate(v[1].w)
             && predicate(v[2].x) && predicate(v[2].y) && predicate(v[2].z) && predicate(v[2].w)
             && predicate(v[3].x) && predicate(v[3].y) && predicate(v[3].z) && predicate(v[3].w);
    else
      static_assert(false, "Unsupported number of components");
  }

  /// @brief Checks if none of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @param v The matrix to check.
  /// @returns True if none of the components satisfied the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL,
            IsPredicateCallableT<TComponent> TFunc>
  constexpr bool NoneOf(const matrix_t<TComponent, RL, CL> &v, TFunc predicate) noexcept
  {
    if constexpr (RL == 2 && CL == 2)
      return !predicate(v[0].x) && !predicate(v[0].y) && !predicate(v[1].x) && !predicate(v[1].y);
    else if constexpr (RL == 3 && CL == 3)
      return !predicate(v[0].x) && !predicate(v[0].y) && !predicate(v[0].z) && !predicate(v[1].x)
             && !predicate(v[1].y) && !predicate(v[1].z) && !predicate(v[2].x) && !predicate(v[2].y)
             && !predicate(v[2].z);
    else if constexpr (RL == 4 && CL == 4)
      return !predicate(v[0].x) && !predicate(v[0].y) && !predicate(v[0].z) && !predicate(v[0].w)
             && !predicate(v[1].x) && !predicate(v[1].y) && !predicate(v[1].z) && !predicate(v[1].w)
             && !predicate(v[2].x) && !predicate(v[2].y) && !predicate(v[2].z) && !predicate(v[2].w)
             && !predicate(v[3].x) && !predicate(v[3].y) && !predicate(v[3].z) && !predicate(v[3].w);
    else
      static_assert(false, "Unsupported number of components");
  }
}