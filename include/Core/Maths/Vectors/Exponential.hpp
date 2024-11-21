#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Scalars/Exponential.hpp"
#include "Core/Maths/Vectors/Algorithms.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise `Pow` operation on `base` and `exponent` vectors.
  /// @tparam TComponent The underlying arithmetic type of the vectors.
  /// @tparam L The length of the vectors.
  /// @param base The base vector.
  /// @param exponent The exponent vector.
  /// @returns A vector where each component is `base[i]` raised to the power of `exponent[i]`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Pow(const vector_t<TComponent, L> &base,
                                                   const vector_t<TComponent, L> &exponent) noexcept
  {
    using T = TComponent;
    return MTL::Zip<T, T, T, L>(base, exponent, [](T b, T e) -> T { return MTL::Pow(b, e); });
  }

  /// @brief Computes the natural exponential function (`e^x`) for each component in the input vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is `e^x` for the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Exp(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return MTL::Exp(x); });
  }

  /// @brief Computes `2^x` for each component in the input vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is `2^x` for the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Exp2(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return MTL::Exp2(x); });
  }

  /// @brief Computes `10^x` for each component in the input vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is `10^x` for the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Exp10(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return MTL::Pow(static_cast<T>(10), x); });
  }

  /// @brief Computes the natural logarithm (`ln(x)`) for each component in the input vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is `ln(x)` for the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Log(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return MTL::Log(x); });
  }

  /// @brief Computes the base-2 logarithm (`log2(x)`) for each component in the input vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is `log2(x)` for the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Log2(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return MTL::Log2(x); });
  }

  /// @brief Computes the square root of each component in the input vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is the square root of the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Sqrt(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return MTL::Sqrt(x); });
  }

  /// @brief Computes the inverse square root (`1 / sqrt(x)`) of each component in the input vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is `1 / sqrt(x)` for the corresponding input.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> InverseSqrt(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return static_cast<T>(1) / MTL::Sqrt(x); });
  }

  /// @brief Computes the factorial of each component in the input vector.
  /// @tparam TComponent The underlying unsigned integer type of the vector.
  /// @tparam L The length of the vector.
  /// @param v The input vector.
  /// @returns A vector where each component is the factorial of the corresponding input.
  template <IsUnsignedT TComponent, vec_length_t L>
  constexpr NO_DISCARD vector_t<TComponent, L> Factorial(const vector_t<TComponent, L> &v) noexcept
  {
    using T = TComponent;
    return MTL::Map<T, T, L>(v, [](T x) -> T { return MTL::Factorial(x); });
  }
}
