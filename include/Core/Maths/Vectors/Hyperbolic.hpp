#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Hyperbolic.hpp"
#include "Core/Maths/Vectors/Algorithms.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Computes the hyperbolic sine for each component in `v`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Sinh(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Sinh<T>(val); });
  }

  /// @brief Computes the hyperbolic cosine for each component in `v`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Cosh(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Cosh<T>(val); });
  }

  /// @brief Computes the hyperbolic tangent for each component in `v`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Tanh(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Tanh<T>(val); });
  }

  /// @brief Computes the inverse hyperbolic sine for each component in `v`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Asinh(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Asinh<T>(val); });
  }

  /// @brief Computes the inverse hyperbolic cosine for each component in `v`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Acosh(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Acosh<T>(val); });
  }

  /// @brief Computes the inverse hyperbolic tangent for each component in `v`.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @returns The converted vector.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Atanh(vector_t<TComponent, L> v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T val) -> T { return MTL::Atanh<T>(val); });
  }
}