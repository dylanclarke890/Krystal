#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Trigonometric.hpp"
#include "Core/Maths/Vectors/Algorithms.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Converts each component in `v` to radians.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Radians(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Radians<T>(val); });
  }

  /// @brief Converts each component in `v` to degrees.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Degrees(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Degrees<T>(val); });
  }

  /// @brief Computes sine for each component in `v`.
  /// Each component should be an angle represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Sin(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Sin<T>(val); });
  }

  /// @brief Computes cosine for each component in `v`.
  /// Each component should be an angle represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Cos(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Cos<T>(val); });
  }

  /// @brief Computes tangent for each component in `v`.
  /// Each component should be an angle represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Tan(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Tan<T>(val); });
  }

  /// @brief Computes arc sine for each component in `v`.
  /// Each component should be an angle represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Asin(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Asin<T>(val); });
  }

  /// @brief Computes arc cosine for each component in `v`.
  /// Each component should be an angle represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Acos(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Acos<T>(val); });
  }

  /// @brief Computes arc tangent for each component in `v`.
  /// Each component should be an angle represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Atan(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Atan<T>(val); });
  }

  /// @brief Computes arc tangent for each component in `v`, using signs to determine quadrants.
  /// Each component should be an angle represented in radians.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Atan2(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Atan2<T>(val); });
  }
}