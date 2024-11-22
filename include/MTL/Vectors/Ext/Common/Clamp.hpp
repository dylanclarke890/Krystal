#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Clamp.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Clamps each component of the vector between the corresponding components of the `min` and `max`
  /// vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param value The input vector to clamp.
  /// @param min The vector containing the minimum values.
  /// @param max The vector containing the maximum values.
  /// @return A vector where each component is clamped between the corresponding components of `min` and
  /// `max`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Clamp(const vector_t<TComponent, L> &value,
                                                     const vector_t<TComponent, L> &min,
                                                     const vector_t<TComponent, L> &max) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, L>(value, min, max,
                                [](T v, T mn, T mx) -> T { return MTL::Min(MTL::Max(v, mn), mx); });
  }

  /// @brief Clamps each component of the vector between the scalar values `min` and `max`.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param value The input vector to clamp.
  /// @param min The minimum scalar value for clamping.
  /// @param max The maximum scalar value for clamping.
  /// @return A vector where each component is clamped between `min` and `max`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Clamp(const vector_t<TComponent, L> &value, TComponent min,
                                                     TComponent max) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, T, L>(value, vector_t<T, L>(min), vector_t<T, L>(max),
                                [](T v, T mn, T mx) -> T { return MTL::Min(MTL::Max(v, mn), mx); });
  }
}
