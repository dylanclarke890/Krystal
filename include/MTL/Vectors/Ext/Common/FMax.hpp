#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/FMax.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise maximum operation between two floating point vectors, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @return A vector where each component is the larger of the corresponding components of `a` and `b`, or
  /// `b` if `a` is NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> FMax(const vector_t<TComponent, L> &a,
                                                    const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Zip(a, b, [](TComponent x, TComponent y) -> TComponent { return MTL::FMax(x, y); });
  }

  /// @brief Performs a component-wise maximum operation between three floating point vectors, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @param c The third input vector.
  /// @return A vector where each component is the largest of the corresponding components of `a`, `b` and
  /// `c`,ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> FMax(const vector_t<TComponent, L> &a,
                                                    const vector_t<TComponent, L> &b,
                                                    const vector_t<TComponent, L> &c) noexcept
  {
    return MTL::Zip(a, b, c, [](TComponent x, TComponent y, TComponent z) -> TComponent
                    { return MTL::FMax(x, y, z); });
  }

  /// @brief Performs a component-wise maximum operation between the vector `a` and floating point `b`.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The maximum value each component is allowed to be.
  /// @return A vector where each component is the larger of the corresponding component of `a` and `b`,
  /// ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> FMax(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    return MTL::Zip(a, vector_t<TComponent, L>(b),
                    [](TComponent x, TComponent y) -> TComponent { return MTL::FMax(x, y); });
  }
}