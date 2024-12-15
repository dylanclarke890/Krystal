#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Vectors/Base.hpp"

#include <limits>

namespace Krys::MTL
{
  /// @brief Applies a function to each component of the vector.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @tparam TFunc A callable object or lambda that takes a single `TComponent` as argument. The return value
  /// is always ignored.
  /// @param v The input vector.
  /// @param func The function to be applied to each component of the input vector.
  template <IsArithmeticT TComponent, vec_length_t L, IsRegularCallableT<TComponent> TFunc>
  constexpr void ForEach(const vector_t<TComponent, L> &v, TFunc func) noexcept
  {
    static_assert(L <= 4, "Unsupported number of components.");
    for (vec_length_t i = 0; i < v.GetLength(); i++)
      func(v[i]);
  }

  /// @brief Creates a new vector by applying a function to each component of the input vector.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam TFunc A callable object or lambda that takes a single `TComponent` as argument.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @param func The function to be applied to each component of the input vector.
  /// @return A new vector that is the result of the transformation.
  template <IsArithmeticT TComponent, vec_length_t L, typename TFunc>
  NO_DISCARD constexpr auto MapEach(const vector_t<TComponent, L> &v,
                                    TFunc func) noexcept -> vector_t<decltype(func(declval<TComponent>())), L>
  {
    static_assert(L <= 4, "Unsupported number of components");

    vector_t<decltype(func(declval<TComponent>())), L> vec;
    for (vec_length_t i = 0; i < v.GetLength(); i++)
      vec[i] = func(v[i]);
    return vec;
  }

  /// @brief Creates a new vector from two input vectors by applying a function to each component pair of
  /// the input vectors.
  /// @tparam TComponentA The underlying arithmetic type of the first input vector.
  /// @tparam TComponentB The underlying arithmetic type of the second input vector.
  /// @tparam L The length of the input vectors.
  /// @param v The input vector.
  /// @param func A callable object or lambda that returns the transformed value for each component pair.
  /// @return A new vector that is the result of the transformation.
  template <IsArithmeticT TComponentA, IsArithmeticT TComponentB, vec_length_t L, typename TFunc>
  NO_DISCARD constexpr auto
    Zip(const vector_t<TComponentA, L> &a, const vector_t<TComponentB, L> &b,
        TFunc func) noexcept -> vector_t<decltype(func(declval<TComponentA>(), declval<TComponentB>())), L>
  {
    static_assert(L <= 4, "Unsupported number of components");

    using TReturn = decltype(func(declval<TComponentA>(), declval<TComponentB>()));
    if constexpr (L == 1)
      return vector_t<TReturn, 1>(func(a.x, b.x));
    else if constexpr (L == 2)
      return vector_t<TReturn, 2>(func(a.x, b.x), func(a.y, b.y));
    else if constexpr (L == 3)
      return vector_t<TReturn, 3>(func(a.x, b.x), func(a.y, b.y), func(a.z, b.z));
    else if constexpr (L == 4)
      return vector_t<TReturn, 4>(func(a.x, b.x), func(a.y, b.y), func(a.z, b.z), func(a.w, b.w));
  }

  /// @brief Creates a new vector from three input vectors by applying a function to each component triplet of
  /// the input vectors.
  /// @tparam TComponentA The underlying arithmetic type of the first input vector.
  /// @tparam TComponentB The underlying arithmetic type of the second input vector.
  /// @tparam TComponentC The underlying arithmetic type of the third input vector.
  /// @tparam L The length of the input vectors.
  /// @param v The input vector.
  /// @param func A callable object or lambda that returns the transformed value for each component triplet.
  /// @return A new vector that is the result of the transformation.
  template <IsArithmeticT TComponentA, IsArithmeticT TComponentB, IsArithmeticT TComponentC, vec_length_t L,
            typename TFunc>
  NO_DISCARD constexpr auto Zip(const vector_t<TComponentA, L> &a, const vector_t<TComponentB, L> &b,
                                const vector_t<TComponentC, L> &c, TFunc func) noexcept
    -> vector_t<decltype(func(declval<TComponentA>(), declval<TComponentB>(), declval<TComponentC>())), L>
  {
    static_assert(L <= 4, "Unsupported number of components");

    using TReturn = decltype(func(declval<TComponentA>(), declval<TComponentB>(), declval<TComponentC>()));
    if constexpr (L == 1)
      return vector_t<TReturn, 1>(func(a.x, b.x, c.x));
    else if constexpr (L == 2)
      return vector_t<TReturn, 2>(func(a.x, b.x, c.x), func(a.y, b.y, c.y));
    else if constexpr (L == 3)
      return vector_t<TReturn, 3>(func(a.x, b.x, c.x), func(a.y, b.y, c.y), func(a.z, b.z, c.z));
    else if constexpr (L == 4)
      return vector_t<TReturn, 4>(func(a.x, b.x, c.x), func(a.y, b.y, c.y), func(a.z, b.z, c.z),
                                  func(a.w, b.w, c.w));
  }

  /// @brief Computes the sum of all components of the vector.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @return The sum of the components of `v`.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr TComponent Sum(const vector_t<TComponent, L> &v) noexcept
  {
    static_assert(L <= 4, "Unsupported number of components");

    if constexpr (L == 1)
      return TComponent(v.x);
    else if constexpr (L == 2)
      return TComponent(v.x + v.y);
    else if constexpr (L == 3)
      return TComponent(v.x + v.y + v.z);
    else if constexpr (L == 4)
      return TComponent(v.x + v.y + v.z + v.w);
  }

  /// @brief Computes the sum of all components of the vector after applying a function to each component.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @param func A callable object or lambda to transform each component before summing.
  /// @return The sum of the transformed components of `v`.
  template <IsArithmeticT TComponent, vec_length_t L, IsRegularCallableT<TComponent> TFunc>
  NO_DISCARD constexpr TComponent Sum(const vector_t<TComponent, L> &v, TFunc func) noexcept
  {
    static_assert(L <= 4, "Unsupported number of components");

    if constexpr (L == 1)
      return TComponent(func(v.x));
    else if constexpr (L == 2)
      return TComponent(func(v.x) + func(v.y));
    else if constexpr (L == 3)
      return TComponent(func(v.x) + func(v.y) + func(v.z));
    else if constexpr (L == 4)
      return TComponent(func(v.x) + func(v.y) + func(v.z) + func(v.w));
  }

  /// @brief Reverses a vector.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @return The new vector in which the components are reversed.
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Reverse(const vector_t<TComponent, L> &v) noexcept -> vector_t<TComponent, L>
  {
    static_assert(L <= 4, "Unsupported number of components");

    if constexpr (L == 1)
      return vector_t<TComponent, 1>(v.x);
    else if constexpr (L == 2)
      return vector_t<TComponent, 2>(v.y, v.x);
    else if constexpr (L == 3)
      return vector_t<TComponent, 3>(v.z, v.y, v.x);
    else if constexpr (L == 4)
      return vector_t<TComponent, 4>(v.w, v.z, v.y, v.x);
  }

  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto MinOf(const vector_t<TComponent, L> &v) noexcept -> TComponent
  {
    TComponent min = std::numeric_limits<TComponent>::max();
    ForEach(v, [&min](TComponent val) { min = (val < min) ? val : min; });
    return min;
  }

  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto MaxOf(const vector_t<TComponent, L> &v) noexcept -> TComponent
  {
    TComponent max = std::numeric_limits<TComponent>::lowest();
    ForEach(v, [&max](TComponent val) { max = (val > max) ? val : max; });
    return max;
  }
}