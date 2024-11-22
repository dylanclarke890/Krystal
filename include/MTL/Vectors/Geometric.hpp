#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Exponential.hpp"
#include "Core/Maths/Vectors/Algorithms.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Computes the dot product of two vectors.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first vector.
  /// @param b The second vector.
  /// @return The dot product of `a` and `b`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr TComponent Dot(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b) noexcept;

  /// @brief Computes the length (magnitude) of a vector.
  /// @tparam TComponent The underlying floating-point type of the vector.
  /// @tparam L The length of the vector.
  /// @param x The input vector.
  /// @return The length of the vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr TComponent Length(const vector_t<TComponent, L> &x) noexcept
  {
    return MTL::Sqrt<TComponent>(MTL::Dot<TComponent, L>(x, x));
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
    return MTL::Length<TComponent, L>(a - b);
  }

  /// @brief Normalizes a vector (scales it to length 1).
  /// @tparam TComponent The underlying floating-point type of the vector.
  /// @tparam L The length of the vector.
  /// @param x The input vector.
  /// @return A normalized version of the vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr vector_t<TComponent, L> Normalize(const vector_t<TComponent, L> &x) noexcept
  {
    return x * MTL::InverseSqrt<TComponent>(MTL::Dot<TComponent, L>(x, x));
  }

  /// @brief Computes the cross product of two 3D vectors.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @param a The first vector.
  /// @param b The second vector.
  /// @return The cross product of `a` and `b`.
  template <IsFloatingPointT TComponent>
  constexpr vector_t<TComponent, 3> Cross(const vector_t<TComponent, 3> &a,
                                          const vector_t<TComponent, 3> &b) noexcept
  {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
  }

  /// @brief Projects vector `a` onto vector `b`.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The vector to project.
  /// @param b The vector to project onto.
  /// @return The projection of `a` onto `b`.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr vector_t<TComponent, L> Project(const vector_t<TComponent, L> &a,
                                            const vector_t<TComponent, L> &b) noexcept
  {
    return b * (MTL::Dot<TComponent, L>(a, b) / MTL::Dot<TComponent, L>(b, b));
  }

  /// @brief Reflects vector `v` across the normal `n`.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param v The input vector to reflect.
  /// @param n The normal vector to reflect across (should be normalized).
  /// @return The reflected vector.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr vector_t<TComponent, L> Reflect(const vector_t<TComponent, L> &v,
                                            const vector_t<TComponent, L> &n) noexcept
  {
    return v - TComponent(2) * MTL::Dot<TComponent, L>(v, n) * n;
  }

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

#pragma region Dot

  template <IsFloatingPointT TComponent>
  constexpr TComponent Dot(const vector_t<TComponent, 1> &a, const vector_t<TComponent, 1> &b) noexcept
  {
    return a.x * b.x;
  }

  template <IsFloatingPointT TComponent>
  constexpr TComponent Dot(const vector_t<TComponent, 2> &a, const vector_t<TComponent, 2> &b) noexcept
  {
    return a.x * b.x + a.y * b.y;
  }

  template <IsFloatingPointT TComponent>
  constexpr TComponent Dot(const vector_t<TComponent, 3> &a, const vector_t<TComponent, 3> &b) noexcept
  {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  template <IsFloatingPointT TComponent>
  constexpr TComponent Dot(const vector_t<TComponent, 4> &a, const vector_t<TComponent, 4> &b) noexcept
  {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
  }

#pragma endregion Dot
}
