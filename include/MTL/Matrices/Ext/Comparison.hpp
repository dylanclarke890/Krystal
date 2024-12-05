#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"
#include "MTL/Matrices/Ext/Predicate.hpp"

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
  NO_DISCARD constexpr auto LessThan(const matrix_t<TComponent, CL, RL> &a,
                                     const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent a, TComponent b) -> bool { return a < b; });
  }

  /// @brief Performs a component-wise `<` comparison between matrix `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are less than `b`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto LessThan(const matrix_t<TComponent, CL, RL> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v < b; });
  }

  /// @brief Performs a component-wise `<=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto LessThanOrEqual(const matrix_t<TComponent, CL, RL> &a,
                                            const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent a, TComponent b) -> bool { return a <= b; });
  }

  /// @brief Performs a component-wise `<=` comparison between matrix `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are less than or equal to `b`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto LessThanOrEqual(const matrix_t<TComponent, CL, RL> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v <= b; });
  }

  /// @brief Performs a component-wise `==` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto Equal(const matrix_t<TComponent, CL, RL> &a,
                                  const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent a, TComponent b) -> bool { return a == b; });
  }

  /// @brief Performs a component-wise `==` comparison between matrix `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are equal to `b`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto Equal(const matrix_t<TComponent, CL, RL> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v == b; });
  }

  /// @brief Performs a component-wise `!=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto NotEqual(const matrix_t<TComponent, CL, RL> &a,
                                     const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent a, TComponent b) -> bool { return a != b; });
  }

  /// @brief Performs a component-wise `!=` comparison between matrix `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are not equal to `b`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto NotEqual(const matrix_t<TComponent, CL, RL> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v != b; });
  }

  /// @brief Performs a component-wise `>` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto GreaterThan(const matrix_t<TComponent, CL, RL> &a,
                                        const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent a, TComponent b) -> bool { return a > b; });
  }

  /// @brief Performs a component-wise `>` comparison between matrix `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are greater than `b`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto GreaterThan(const matrix_t<TComponent, CL, RL> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v > b; });
  }

  /// @brief Performs a component-wise `>=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrices.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `CL`, `RL` size bool matrix where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto GreaterThanOrEqual(const matrix_t<TComponent, CL, RL> &a,
                                               const matrix_t<TComponent, CL, RL> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent a, TComponent b) -> bool { return a >= b; });
  }

  /// @brief Performs a component-wise `>=` comparison between matrix `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are greater than or equal to `b`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto GreaterThanOrEqual(const matrix_t<TComponent, CL, RL> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v >= b; });
  }
}