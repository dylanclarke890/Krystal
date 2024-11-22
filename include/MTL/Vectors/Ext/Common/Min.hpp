#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Min.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise minimum operation between two vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @return A vector where each component is the smaller of the corresponding components of `a` and `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Min(const vector_t<TComponent, L> &a,
                                                   const vector_t<TComponent, L> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, L>(a, b, [](T x, T y) -> T { return MTL::Min(x, y); });
  }

  /// @brief Performs a component-wise minimum operation between three vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @param c The third input vector.
  /// @return A vector where each component is the smallest of the corresponding components of `a`, `b` and
  /// `c`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Min(const vector_t<TComponent, L> &a,
                                                   const vector_t<TComponent, L> &b,
                                                   const vector_t<TComponent, L> &c) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, L>(a, b, c, [](T x, T y, T z) -> T { return MTL::Min(x, y, z); });
  }

  /// @brief Performs a component-wise minimum operation between four vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @param c The third input vector.
  /// @param d The fourth input vector.
  /// @return A vector where each component is the smallest of the corresponding components of `a`, `b`, `c`
  /// and `d`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L>
    Min(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b, const vector_t<TComponent, L> &c,
        const vector_t<TComponent, L> &d) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, T, L>(a, b, c, d, [](T x, T y, T z, T w) -> T { return MTL::Min(x, y, z, w); });
  }

  /// @brief Performs a component-wise minimum operation between the vector `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The minimum value each component is allowed to be.
  /// @return A vector where each component is the smaller of the corresponding component of `a` and `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Min(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, L>(a, vector_t<T, L>(b), [](T x, T y) -> T { return MTL::Min(x, y); });
  }
}