#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Geometric.hpp"
#include "MTL/Vectors/Ext/MinMax.hpp"

namespace Krys::MTL
{
  /// @brief Check whether two vectors are collinears.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr bool AreCollinear(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b,
                                         const TComponent &epsilon) noexcept
  {
    using cross_t = vector_t<TComponent, 3>;
    constexpr auto Collinear = [](cross_t a, cross_t b, TComponent epsilon) -> bool
    {
      return MTL::Length(MTL::Cross(a, b)) < epsilon;
    };

    if constexpr (L == 2)
    {
      return Collinear({a.x, a.y, TComponent(0)}, {b.x, b.y, TComponent(0)}, epsilon);
    }
    else if constexpr (L == 3)
    {
      return Collinear(a, b, epsilon);
    }
    else if constexpr (L == 4)
    {
      return Collinear({a.x, a.y, a.z}, {b.x, b.y, b.z}, epsilon);
    }
    else
      static_assert(false, "Unsupported vector size.");
  }

  /// @brief Check whether two vectors are orthogonals.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr bool AreOrthogonal(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b,
                                          const TComponent &epsilon) noexcept
  {
    return MTL::Abs(MTL::Dot(a, b))
           <= MTL::Max(TComponent(1), MTL::Length(a)) * MTL::Max(TComponent(1), MTL::Length(b)) * epsilon;
  }

  /// @brief Check whether a vector is normalized.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr bool IsNormalized(const vector_t<TComponent, L> &v, const TComponent &epsilon) noexcept
  {
    return MTL::Abs(MTL::Length(v) - TComponent(1)) <= TComponent(2) * epsilon;
  }

  /// @brief Check whether a vector is null.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr bool IsNull(const vector_t<TComponent, L> &v, const TComponent &epsilon) noexcept
  {
    return MTL::Length(v) <= epsilon;
  }

  /// @brief Check whether two vectors are orthonormal.
  template <IsFloatingPointT TComponent, vec_length_t L>
  NO_DISCARD constexpr bool AreOrthonormal(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b,
                                           const TComponent &epsilon) noexcept
  {
    return MTL::IsNormalized(a, epsilon) && MTL::IsNormalized(b, epsilon)
           && (MTL::Abs(MTL::Dot(a, b)) <= epsilon);
  }
}