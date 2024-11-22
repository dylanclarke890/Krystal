#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Limits.hpp"
#include "Core/Maths/Vectors/Algorithms.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
#pragma region Min

  /// @brief Performs a component-wise minimum operation between two vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @return A vector where each component is the smaller of the corresponding components of `a` and `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Min(const vector_t<TComponent, L> &a,
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
  constexpr NO_DISCARD vector_t<TComponent, L> Min(const vector_t<TComponent, L> &a,
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
  constexpr NO_DISCARD vector_t<TComponent, L>
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
  constexpr NO_DISCARD vector_t<TComponent, L> Min(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, L>(a, vector_t<T, L>(b), [](T x, T y) -> T { return MTL::Min(x, y); });
  }

#pragma endregion Min

#pragma region FMin

  /// @brief Performs a component-wise minimum operation between two floating point vectors, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @return A vector where each component is the smaller of the corresponding components of `a` and `b`, or
  /// `b` if `a` is NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> FMin(const vector_t<TComponent, L> &a,
                                                    const vector_t<TComponent, L> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, L>(a, b, [](T x, T y) -> T { return MTL::FMin(x, y); });
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
  constexpr NO_DISCARD vector_t<TComponent, L> FMin(const vector_t<TComponent, L> &a,
                                                    const vector_t<TComponent, L> &b,
                                                    const vector_t<TComponent, L> &c) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, L>(a, b, c, [](T x, T y, T z) -> T { return MTL::FMin(x, y, z); });
  }

  /// @brief Performs a component-wise minimum operation between four floating point vectors, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @param c The third input vector.
  /// @param d The fourth input vector.
  /// @return A vector where each component is the smallest of the corresponding components of `a`, `b`, `c`
  /// and `d`,ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L>
    FMin(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b, const vector_t<TComponent, L> &c,
         const vector_t<TComponent, L> &d) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, T, L>(a, b, c, d, [](T x, T y, T z, T w) -> T { return MTL::FMin(x, y, z, w); });
  }

  /// @brief Performs a component-wise minimum operation between the vector `a` and floating point `b`.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The minimum value each component is allowed to be.
  /// @return A vector where each component is the smaller of the corresponding component of `a` and `b`,
  /// ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> FMin(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, L>(a, vector_t<T, L>(b), [](T x, T y) -> T { return MTL::FMin(x, y); });
  }

#pragma endregion FMin

#pragma region Max

  /// @brief Performs a component-wise maximum operation between two vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @return A vector where each component is the larger of the corresponding components of `a` and `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Max(const vector_t<TComponent, L> &a,
                                                   const vector_t<TComponent, L> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, L>(a, b, [](T x, T y) -> T { return MTL::Max(x, y); });
  }

  /// @brief Performs a component-wise maximum operation between three vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @param c The third input vector.
  /// @return A vector where each component is the largest of the corresponding components of `a`, `b` and
  /// `c`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Max(const vector_t<TComponent, L> &a,
                                                   const vector_t<TComponent, L> &b,
                                                   const vector_t<TComponent, L> &c) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, L>(a, b, c, [](T x, T y, T z) -> T { return MTL::Max(x, y, z); });
  }

  /// @brief Performs a component-wise maximum operation between four vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @param c The third input vector.
  /// @param d The fourth input vector.
  /// @return A vector where each component is the largest of the corresponding components of `a`, `b`, `c`
  /// and `d`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L>
    Max(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b, const vector_t<TComponent, L> &c,
        const vector_t<TComponent, L> &d) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, T, L>(a, b, c, d, [](T x, T y, T z, T w) -> T { return MTL::Max(x, y, z, w); });
  }

  /// @brief Performs a component-wise maximum operation between the vector `a` and scalar `b`.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The maximum value each component is allowed to be.
  /// @return A vector where each component is the larger of the corresponding component of `a` and `b`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Max(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    using T = TComponent;
    return MTL::Max<T, L>(a, vector_t<T, L>(b), [](T x, T y) -> T { return MTL::Max(x, y); });
  }

#pragma endregion Max

#pragma region FMax

  /// @brief Performs a component-wise maximum operation between two floating point vectors, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @return A vector where each component is the larger of the corresponding components of `a` and `b`, or
  /// `b` if `a` is NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> FMax(const vector_t<TComponent, L> &a,
                                                    const vector_t<TComponent, L> &b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, L>(a, b, [](T x, T y) -> T { return MTL::FMax(x, y); });
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
  constexpr NO_DISCARD vector_t<TComponent, L> FMax(const vector_t<TComponent, L> &a,
                                                    const vector_t<TComponent, L> &b,
                                                    const vector_t<TComponent, L> &c) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, L>(a, b, c, [](T x, T y, T z) -> T { return MTL::FMax(x, y, z); });
  }

  /// @brief Performs a component-wise maximum operation between four floating point vectors, ignoring NaN.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The second input vector.
  /// @param c The third input vector.
  /// @param d The fourth input vector.
  /// @return A vector where each component is the largest of the corresponding components of `a`, `b`, `c`
  /// and `d`,ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L>
    FMax(const vector_t<TComponent, L> &a, const vector_t<TComponent, L> &b, const vector_t<TComponent, L> &c,
         const vector_t<TComponent, L> &d) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, T, L>(a, b, c, d, [](T x, T y, T z, T w) -> T { return MTL::FMax(x, y, z, w); });
  }

  /// @brief Performs a component-wise maximum operation between the vector `a` and floating point `b`.
  /// @tparam TComponent The underlying floating-point type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param a The first input vector.
  /// @param b The maximum value each component is allowed to be.
  /// @return A vector where each component is the larger of the corresponding component of `a` and `b`,
  /// ignoring NaN.
  template <IsFloatingPointT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> FMax(const vector_t<TComponent, L> &a, TComponent b) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, L>(a, vector_t<T, L>(b), [](T x, T y) -> T { return MTL::FMax(x, y); });
  }

#pragma endregion FMax

#pragma region Clamp

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

#pragma endregion Clamp
}