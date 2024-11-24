#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/FMin.hpp"
#include "MTL/Common/Min.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise minimum operation between two vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @return A vector where each component is the smaller of the corresponding components of `a` and `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Min(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> TComponent { return MTL::Min(x, y); });
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
  NO_DISCARD constexpr auto Min(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b,
                                const vector_t<TComponent, L> &c) noexcept
  {
    return MTL::Zip(a, b, c,
                    [](TComponent x, TComponent y, TComponent z) -> TComponent { return MTL::Min(x, y, z); });
  }

  /// @brief Performs a component-wise minimum operation between the vector `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The minimum value each component is allowed to be.
  /// @return A vector where each component is `b` or the corresponding component of `a`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Min(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    return MTL::MapEach(a, [&b](TComponent v) -> TComponent { return MTL::Min(v, b); });
  }

  /// @brief Performs a component-wise minimum operation between two floating point vectors, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @return A vector where each component is the smaller of the corresponding components of `a` and `b`, or
  /// `b` if `a` is NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto FMin(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> TComponent { return MTL::FMin(x, y); });
  }

  /// @brief Performs a component-wise minimum operation between three floating point vectors, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @param c The third input vector.
  /// @return A vector where each component is the smallest of the corresponding components of `a`, `b` and
  /// `c`,ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto FMin(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b,
                                 const vector_t<TComponent, L> &c) noexcept
  {
    return MTL::Zip(a, b, c, [](TComponent x, TComponent y, TComponent z) -> TComponent
                    { return MTL::FMin(x, y, z); });
  }

  /// @brief Performs a component-wise minimum operation between the vector `a` and floating point `b`.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The minimum value each component is allowed to be.
  /// @return A vector where each component is `b` or the corresponding component of `a`,
  /// ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto FMin(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    return MTL::MapEach(a, [&b](TComponent v) -> TComponent { return MTL::FMin(v, b); });
  }
}