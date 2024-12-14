#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Power/InverseSqrt.hpp"
#include "MTL/Power/Sqrt.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"

namespace Krys::MTL
{
  /// @brief Computes the dot product of two vectors.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first vector.
  /// @param b The second vector.
  /// @return The dot product of `a` and `b`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr TComponent Dot(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept
  {
    static_assert(L <= 4, "Unsupported number of components");
    
    if constexpr (L == 1)
      return a.x * b.x;
    else if constexpr (L == 2)
      return a.x * b.x + a.y * b.y;
    else if constexpr (L == 3)
      return a.x * b.x + a.y * b.y + a.z * b.z;
    else if constexpr (L == 4)
      return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
  }

  /// @brief Computes the length (magnitude) of a vector.
  /// @tparam TComponent The underlying floating-point type of the vector.
  /// @tparam L The length of the vector.
  /// @param x The input vector.
  /// @return The length of the vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr TComponent Length(const vector_t<TComponent, L> &x) noexcept
  {
    return MTL::Sqrt(MTL::Dot(x, x));
  }

  /// @brief Computes the squared length (magnitude) of a vector.
  /// @tparam TComponent The underlying floating-point type of the vector.
  /// @tparam L The length of the vector.
  /// @param x The input vector.
  /// @return The squared length of the vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr TComponent LengthSquared(const vector_t<TComponent, L> &x) noexcept
  {
    return MTL::Dot(x, x);
  }

  /// @brief Normalizes a vector (scales it to length 1).
  /// @tparam TComponent The underlying floating-point type of the vector.
  /// @tparam L The length of the vector.
  /// @param x The input vector.
  /// @return A normalized version of the vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr auto Normalize(const vector_t<TComponent, L> &x) noexcept
  {
    return x * MTL::InverseSqrt(MTL::Dot(x, x));
  }

  /// @brief Computes the distance between two vectors.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first vector.
  /// @param b The second vector.
  /// @return The distance between `a` and `b`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr TComponent Distance(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::Length(a - b);
  }

  /// @brief Computes the squared distance between two vectors.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first vector.
  /// @param b The second vector.
  /// @return The squared distance between `a` and `b`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr TComponent DistanceSquared(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept
  {
    return MTL::LengthSquared(a - b);
  }

  /// @brief Projects vector `a` onto vector `b`.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The vector to project.
  /// @param b The vector to project onto.
  /// @return The projection of `a` onto `b`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr auto Project(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept
  {
    return b * (MTL::Dot(a, b) / MTL::Dot(b, b));
  }

  /// @brief Reflects vector `v` across the normal `n`.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param v The input vector to reflect.
  /// @param n The normal vector to reflect across (should be normalized).
  /// @return The reflected vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr auto Reflect(const vector_t<TComponent, L> &v, const vector_t<TComponent, L> &n) noexcept
  {
    return v - n * MTL::Dot(n, v) * TComponent(2);
  }

  /// @brief Computes the refraction of vector `v` given a normal `n` and a refraction index.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param v The incident vector.
  /// @param n The normal vector (should be normalized).
  /// @param eta The refraction index.
  /// @return The refracted vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr auto Refract(const vector_t<TComponent, L> &v, const vector_t<TComponent, L> &n,
                         TComponent eta) noexcept
  {
    TComponent dot = MTL::Dot(v, n);
    TComponent k = TComponent(1) - eta * eta * (TComponent(1) - dot * dot);
    if (k < TComponent(0))
      return vector_t<TComponent, L>(0); // Total internal reflection
    return eta * v - (eta * dot + MTL::Sqrt(k)) * n;
  }

  /// @brief Computes the cross product of two 3D vectors.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @param a The first vector.
  /// @param b The second vector.
  /// @return The cross product of `a` and `b`.
  template <IsFloatingPointT TComponent>
  constexpr auto Cross(const vec3_t<TComponent> &a, const vec3_t<TComponent> &b) noexcept
  {
    return vec3_t<TComponent> {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
  }

  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param v The incident vector.
  /// @param n The normal vector (should be normalized).
  /// @return `n` if `Dot(nRef, i)` < `0.0`, otherwise `-n`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr auto FaceForward(const vector_t<TComponent, L> &n, const vector_t<TComponent, L> &i,
                             const vector_t<TComponent, L> &nRef) noexcept
  {
    return MTL::Dot(nRef, i) < static_cast<TComponent>(0) ? n : -n;
  }
}
