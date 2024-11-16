#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Matrices/Algorithms.hpp"
#include "Core/Maths/Matrices/Base.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise `<` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> LessThan(const matrix_t<TComponent, CL, RL> &a,
                                                       const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, CL, RL>(a, b, [](T a, T b) -> bool { return a < b; });
  }

  /// @brief Performs a component-wise `<=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> LessThanOrEqual(const matrix_t<TComponent, CL, RL> &a,
                                                              const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, CL, RL>(a, b, [](T a, T b) -> bool { return a <= b; });
  }

  /// @brief Performs a component-wise `==` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> Equal(const matrix_t<TComponent, CL, RL> &a,
                                                    const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, CL, RL>(a, b, [](T a, T b) -> bool { return a == b; });
  }

  /// @brief Performs a component-wise `!=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> NotEqual(const matrix_t<TComponent, CL, RL> &a,
                                                       const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, CL, RL>(a, b, [](T a, T b) -> bool { return a != b; });
  }

  /// @brief Performs a component-wise `>` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL> GreaterThan(const matrix_t<TComponent, CL, RL> &a,
                                                          const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, CL, RL>(a, b, [](T a, T b) -> bool { return a > b; });
  }

  /// @brief Performs a component-wise `>=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  constexpr NO_DISCARD matrix_t<bool, CL, RL>
    GreaterThanOrEqual(const matrix_t<TComponent, CL, RL> &a, const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, CL, RL>(a, b, [](T a, T b) -> bool { return a >= b; });
  }
}