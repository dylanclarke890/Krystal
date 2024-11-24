#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"
#include "MTL/Vectors/Ext/Predicate.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise `<` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto LessThan(const vector_t<TComponent, L> &a,
                                     const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> bool { return x < y; });
  }

  /// @brief Performs a component-wise `<` comparison between vector `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are less than `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto LessThan(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v < b; });
  }

  /// @brief Performs a component-wise `<=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto LessThanOrEqual(const vector_t<TComponent, L> &a,
                                            const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> bool { return x <= y; });
  }

  /// @brief Performs a component-wise `<=` comparison between vector `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are less than or equal to `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto LessThanOrEqual(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v <= b; });
  }

  /// @brief Performs a component-wise `==` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Equal(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> bool { return x == y; });
  }

  /// @brief Performs a component-wise `==` comparison between vector `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are equal to `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Equal(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v == b; });
  }

  /// @brief Performs a component-wise `!=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto NotEqual(const vector_t<TComponent, L> &a,
                                     const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> bool { return x != y; });
  }

  /// @brief Performs a component-wise `!=` comparison between vector `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are not equal to `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto NotEqual(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v != b; });
  }

  /// @brief Performs a component-wise `>` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto GreaterThan(const vector_t<TComponent, L> &a,
                                        const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> bool { return x > y; });
  }

  /// @brief Performs a component-wise `>` comparison between vector `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are greater than `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto GreaterThan(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v > b; });
  }

  /// @brief Performs a component-wise `>=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto GreaterThanOrEqual(const vector_t<TComponent, L> &a,
                                               const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> bool { return x >= y; });
  }

  /// @brief Performs a component-wise `>=` comparison between vector `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return True if all components of `a` are greater than or equal to `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto GreaterThanOrEqual(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    return MTL::AllOf(a, [&b](TComponent v) -> bool { return v >= b; });
  }
}