#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise `<` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<bool, L> LessThan(const vector_t<TComponent, L> &a,
                                                  const vector_t<TComponent, L> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, L>(a, b, [](T a, T b) -> bool { return a < b; });
  }

  /// @brief Performs a component-wise `<=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<bool, L> LessThanOrEqual(const vector_t<TComponent, L> &a,
                                                         const vector_t<TComponent, L> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, L>(a, b, [](T a, T b) -> bool { return a <= b; });
  }

  /// @brief Performs a component-wise `==` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<bool, L> Equal(const vector_t<TComponent, L> &a,
                                               const vector_t<TComponent, L> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, L>(a, b, [](T a, T b) -> bool { return a == b; });
  }

  /// @brief Performs a component-wise `!=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<bool, L> NotEqual(const vector_t<TComponent, L> &a,
                                                  const vector_t<TComponent, L> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, L>(a, b, [](T a, T b) -> bool { return a != b; });
  }

  /// @brief Performs a component-wise `>` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<bool, L> GreaterThan(const vector_t<TComponent, L> &a,
                                                     const vector_t<TComponent, L> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, L>(a, b, [](T a, T b) -> bool { return a > b; });
  }

  /// @brief Performs a component-wise `>=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the input vectors.
  /// @tparam L The length of the input vectors.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return An `L` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<bool, L> GreaterThanOrEqual(const vector_t<TComponent, L> &a,
                                                            const vector_t<TComponent, L> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, bool, L>(a, b, [](T a, T b) -> bool { return a >= b; });
  }
}