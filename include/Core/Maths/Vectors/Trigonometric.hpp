#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalar/Trigonometric.hpp"
#include "Core/Maths/Vectors/Algorithms.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Converts each component in `v` to radians.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<TComponent, Length> Radians(vector_t<TComponent, Length> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, Length, T>(v, [](T val) { return MTL::Radians<T>(val); });
  }

  /// @brief Converts each component in `v` to degrees.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<TComponent, Length> Degrees(vector_t<TComponent, Length> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, Length, T>(v, [](T val) { return MTL::Degrees<T>(val); });
  }

  /// @brief Computes sine for each component in `v`.
  /// Each component should contain angles represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<TComponent, Length> Sin(vector_t<TComponent, Length> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, Length, T>(v, [](T val) { return MTL::Sin<T>(val); });
  }

  /// @brief Computes cosine for each component in `v`.
  /// Each component should contain angles represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<TComponent, Length> Cos(vector_t<TComponent, Length> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, Length, T>(v, [](T val) { return MTL::Cos<T>(val); });
  }

  /// @brief Computes tangent for each component in `v`.
  /// Each component should contain angles represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<TComponent, Length> Tan(vector_t<TComponent, Length> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, Length, T>(v, [](T val) { return MTL::Tan<T>(val); });
  }

  /// @brief Computes arc sine for each component in `v`.
  /// Each component should contain angles represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<TComponent, Length> Asin(vector_t<TComponent, Length> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, Length, T>(v, [](T val) { return MTL::Asin<T>(val); });
  }

  /// @brief Computes arc cosine for each component in `v`.
  /// Each component should contain angles represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<TComponent, Length> Acos(vector_t<TComponent, Length> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, Length, T>(v, [](T val) { return MTL::Acos<T>(val); });
  }

  /// @brief Computes arc tangent for each component in `v`.
  /// Each component should contain angles represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<TComponent, Length> Atan(vector_t<TComponent, Length> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, Length, T>(v, [](T val) { return MTL::Atan<T>(val); });
  }

  /// @brief Computes arc tangent for each component in `v`, using signs to determine quadrants.
  /// Each component should contain angles represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<TComponent, Length> Atan2(vector_t<TComponent, Length> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, Length, T>(v, [](T val) { return MTL::Atan2<T>(val); });
  }
}