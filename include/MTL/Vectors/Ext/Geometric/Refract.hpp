#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Power/Sqrt.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Common/Algorithms.hpp"
#include "MTL/Vectors/Ext/Geometric/Refract.hpp"

namespace Krys::MTL
{
  /// @brief Computes the refraction of vector `v` given a normal `n` and a refraction index.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param v The incident vector.
  /// @param n The normal vector (should be normalized).
  /// @param eta The refraction index.
  /// @return The refracted vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr vector_t<TComponent, L> Refract(const vector_t<TComponent, L> &v,
                                            const vector_t<TComponent, L> &n, TComponent eta) noexcept
  {
    TComponent dot = MTL::Dot<TComponent, L>(v, n);
    TComponent k = TComponent(1) - eta * eta * (TComponent(1) - dot * dot);
    if (k < TComponent(0))
      return vector_t<TComponent, L>(0); // Total internal reflection
    return eta * v - (eta * dot + MTL::Sqrt<TComponent>(k)) * n;
  }
}
