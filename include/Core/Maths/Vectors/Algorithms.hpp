#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Applies a function to each component of the vector.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @param func A callable object or lambda to be applied to each component.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr void ForEach(const vector_t<TComponent, L> &v, Func<void(TComponent v)> func) noexcept;

  /// @brief Creates a new vector by applying a function to each component of the input vector.
  /// @tparam TComponentIn The underlying arithmetic type of the input vector.
  /// @tparam TOut The underlying arithmetic type of the output vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @param func A callable object or lambda that returns the transformed value for each component.
  /// @return A vector where each component is the result of applying `func` to the corresponding input
  /// component.
  template <IsArithmeticT TComponentIn, IsArithmeticT TOut, vec_length_t L>
  constexpr vector_t<TOut, L> Map(const vector_t<TComponentIn, L> &v,
                                  Func<TOut(TComponentIn v)> func) noexcept;

  /// @brief Creates a new vector from two input vectors by applying a function to each component pair of
  /// the input vectors.
  /// @tparam TComponentInA The underlying arithmetic type of the first input vector.
  /// @tparam TComponentInB The underlying arithmetic type of the second input vector.
  /// @tparam TOut The underlying arithmetic type of the output vector.
  /// @tparam L The length of the input vectors.
  /// @param v The input vector.
  /// @param func A callable object or lambda that returns the transformed value for each component.
  /// @return A vector where each component is the result of applying `func` to the corresponding pair of
  /// input components.
  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TOut, vec_length_t L>
  constexpr vector_t<TOut, L> Zip(const vector_t<TComponentInA, L> &a, const vector_t<TComponentInB, L> &b,
                                  Func<TOut(TComponentInA a, TComponentInB b)> func) noexcept;

  /// @brief Creates a new vector from three input vectors by applying a function to each component triplet of
  /// the input vectors.
  /// @tparam TComponentInA The underlying arithmetic type of the first input vector.
  /// @tparam TComponentInB The underlying arithmetic type of the second input vector.
  /// @tparam TComponentInC The underlying arithmetic type of the third input vector.
  /// @tparam TOut The underlying arithmetic type of the output vector.
  /// @tparam L The length of the input vectors.
  /// @param v The input vector.
  /// @param func A callable object or lambda that returns the transformed value for each component.
  /// @return A vector where each component is the result of applying `func` to the corresponding triplet of
  /// input components.
  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TComponentInC,
            IsArithmeticT TOut, vec_length_t L>
  constexpr vector_t<TOut, L>
    Zip(const vector_t<TComponentInA, L> &a, const vector_t<TComponentInB, L> &b,
        const vector_t<TComponentInC, L> &c,
        Func<TOut(TComponentInA a, TComponentInB b, TComponentInC c)> func) noexcept;

  /// @brief Creates a new vector from three input vectors by applying a function to each component quadruplet
  /// of the input vectors.
  /// @tparam TComponentInA The underlying arithmetic type of the first input vector.
  /// @tparam TComponentInB The underlying arithmetic type of the second input vector.
  /// @tparam TComponentInC The underlying arithmetic type of the third input vector.
  /// @tparam TComponentInD The underlying arithmetic type of the fourth input vector.
  /// @tparam TOut The underlying arithmetic type of the output vector.
  /// @tparam L The length of the input vectors.
  /// @param v The input vector.
  /// @param func A callable object or lambda that returns the transformed value for each component.
  /// @return A vector where each component is the result of applying `func` to the corresponding quadruplet
  /// of input components.
  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TComponentInC,
            IsArithmeticT TComponentInD, IsArithmeticT TOut, vec_length_t L>
  constexpr vector_t<TOut, L>
    Zip(const vector_t<TComponentInA, L> &a, const vector_t<TComponentInB, L> &b,
        const vector_t<TComponentInC, L> &c, const vector_t<TComponentInD, L> &d,
        Func<TOut(TComponentInA a, TComponentInB b, TComponentInC c, TComponentInD d)> func) noexcept;

  /// @brief Computes the sum of all components of the vector.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @return The sum of the components of `v`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, L> &v) noexcept;

  /// @brief Computes the sum of all components of the vector after applying a function to each component.
  /// @tparam TComponent The underlying arithmetic type of the input vector.
  /// @tparam L The length of the input vector.
  /// @param v The input vector.
  /// @param func A callable object or lambda to transform each component before summing.
  /// @return The sum of the transformed components of `v`.
  template <IsArithmeticT TComponent, vec_length_t L>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, L> &v,
                                      Func<TComponent(TComponent v)> func) noexcept;

#pragma region ForEach

  template <IsArithmeticT TComponent>
  constexpr void ForEach(const vector_t<TComponent, 1> &v, Func<void(TComponent)> func) noexcept
  {
    func(v.x);
  }

  template <IsArithmeticT TComponent>
  constexpr void ForEach(const vector_t<TComponent, 2> &v, Func<void(TComponent)> func) noexcept
  {
    func(v.x);
    func(v.y);
  }

  template <IsArithmeticT TComponent>
  constexpr void ForEach(const vector_t<TComponent, 3> &v, Func<void(TComponent)> func) noexcept
  {
    func(v.x);
    func(v.y);
    func(v.z);
  }

  template <IsArithmeticT TComponent>
  constexpr void ForEach(const vector_t<TComponent, 4> &v, Func<void(TComponent)> func) noexcept
  {
    func(v.x);
    func(v.y);
    func(v.z);
    func(v.w);
  }

#pragma endregion ForEach

#pragma region Map

  template <IsArithmeticT TComponentIn, IsArithmeticT TOut>
  constexpr vector_t<TOut, 1> Map(const vector_t<TComponentIn, 1> &v, Func<TOut(TComponentIn)> func) noexcept
  {
    return vector_t<TOut, 1>(func(v.x));
  }

  template <IsArithmeticT TComponentIn, IsArithmeticT TOut>
  constexpr vector_t<TOut, 2> Map(const vector_t<TComponentIn, 2> &v, Func<TOut(TComponentIn)> func) noexcept
  {
    return vector_t<TOut, 2>(func(v.x), func(v.y));
  }

  template <IsArithmeticT TComponentIn, IsArithmeticT TOut>
  constexpr vector_t<TOut, 3> Map(const vector_t<TComponentIn, 3> &v, Func<TOut(TComponentIn)> func) noexcept
  {
    return vector_t<TOut, 3>(func(v.x), func(v.y), func(v.z));
  }

  template <IsArithmeticT TComponentIn, IsArithmeticT TOut>
  constexpr vector_t<TOut, 4> Map(const vector_t<TComponentIn, 4> &v, Func<TOut(TComponentIn)> func) noexcept
  {
    return vector_t<TOut, 4>(func(v.x), func(v.y), func(v.z), func(v.w));
  }

#pragma endregion Map

#pragma region Zip

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TOut>
  constexpr vector_t<TOut, 1> Zip(const vector_t<TComponentInA, 1> &a, const vector_t<TComponentInB, 1> &b,
                                  Func<TOut(TComponentInA a, TComponentInB b)> func) noexcept
  {
    return vector_t<TOut, 1>(func(a.x, b.x));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TOut>
  constexpr vector_t<TOut, 2> Zip(const vector_t<TComponentInA, 2> &a, const vector_t<TComponentInB, 2> &b,
                                  Func<TOut(TComponentInA a, TComponentInB b)> func) noexcept
  {
    return vector_t<TOut, 2>(func(a.x, b.x), func(a.y, b.y));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TOut>
  constexpr vector_t<TOut, 3> Zip(const vector_t<TComponentInA, 3> &a, const vector_t<TComponentInB, 3> &b,
                                  Func<TOut(TComponentInA a, TComponentInB b)> func) noexcept
  {
    return vector_t<TOut, 3>(func(a.x, b.x), func(a.y, b.y), func(a.z, b.z));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TOut>
  constexpr vector_t<TOut, 4> Zip(const vector_t<TComponentInA, 4> &a, const vector_t<TComponentInB, 4> &b,
                                  Func<TOut(TComponentInA a, TComponentInB b)> func) noexcept
  {
    return vector_t<TOut, 4>(func(a.x, b.x), func(a.y, b.y), func(a.z, b.z), func(a.w, b.w));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TComponentInC,
            IsArithmeticT TOut>
  constexpr vector_t<TOut, 1> Zip(const vector_t<TComponentInA, 1> &a, const vector_t<TComponentInB, 1> &b,
                                  const vector_t<TComponentInC, 1> &c,
                                  Func<TOut(TComponentInA a, TComponentInB b, TComponentInC c)> func) noexcept
  {
    return vector_t<TOut, 1>(func(a.x, b.x, c.x));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TComponentInC,
            IsArithmeticT TOut>
  constexpr vector_t<TOut, 2> Zip(const vector_t<TComponentInA, 2> &a, const vector_t<TComponentInB, 2> &b,
                                  const vector_t<TComponentInC, 2> &c,
                                  Func<TOut(TComponentInA a, TComponentInB b, TComponentInC c)> func) noexcept
  {
    return vector_t<TOut, 2>(func(a.x, b.x, c.x), func(a.y, b.y, c.y));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TComponentInC,
            IsArithmeticT TOut>
  constexpr vector_t<TOut, 3> Zip(const vector_t<TComponentInA, 3> &a, const vector_t<TComponentInB, 3> &b,
                                  const vector_t<TComponentInC, 3> &c,
                                  Func<TOut(TComponentInA a, TComponentInB b, TComponentInC c)> func) noexcept
  {
    return vector_t<TOut, 3>(func(a.x, b.x, c.x), func(a.y, b.y, c.y), func(a.z, b.z, c.z));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TComponentInC,
            IsArithmeticT TOut>
  constexpr vector_t<TOut, 4> Zip(const vector_t<TComponentInA, 4> &a, const vector_t<TComponentInB, 4> &b,
                                  const vector_t<TComponentInC, 4> &c,
                                  Func<TOut(TComponentInA a, TComponentInB b, TComponentInC c)> func) noexcept
  {
    return vector_t<TOut, 4>(func(a.x, b.x, c.x), func(a.y, b.y, c.y), func(a.z, b.z, c.z),
                             func(a.w, b.w, c.w));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TComponentInC,
            IsArithmeticT TComponentInD, IsArithmeticT TOut>
  constexpr vector_t<TOut, 1> Zip(const vector_t<TComponentInA, 1> &a, const vector_t<TComponentInB, 1> &b,
                                  const vector_t<TComponentInC, 1> &c, const vector_t<TComponentInD, 1> &d,
                                  Func<TOut(TComponentInA a, TComponentInB b, TComponentInC c)> func) noexcept
  {
    return vector_t<TOut, 1>(func(a.x, b.x, c.x, d.x));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TComponentInC,
            IsArithmeticT TComponentInD, IsArithmeticT TOut>
  constexpr vector_t<TOut, 2> Zip(const vector_t<TComponentInA, 2> &a, const vector_t<TComponentInB, 2> &b,
                                  const vector_t<TComponentInC, 2> &c, const vector_t<TComponentInD, 2> &d,
                                  Func<TOut(TComponentInA a, TComponentInB b, TComponentInC c)> func) noexcept
  {
    return vector_t<TOut, 2>(func(a.x, b.x, c.x, d.x), func(a.y, b.y, c.y, d.y));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TComponentInC,
            IsArithmeticT TComponentInD, IsArithmeticT TOut>
  constexpr vector_t<TOut, 3> Zip(const vector_t<TComponentInA, 3> &a, const vector_t<TComponentInB, 3> &b,
                                  const vector_t<TComponentInC, 3> &c, const vector_t<TComponentInD, 3> &d,
                                  Func<TOut(TComponentInA a, TComponentInB b, TComponentInC c)> func) noexcept
  {
    return vector_t<TOut, 3>(func(a.x, b.x, c.x, d.x), func(a.y, b.y, c.y, d.y), func(a.z, b.z, c.z, d.z));
  }

  template <IsArithmeticT TComponentInA, IsArithmeticT TComponentInB, IsArithmeticT TComponentInC,
            IsArithmeticT TComponentInD, IsArithmeticT TOut>
  constexpr vector_t<TOut, 4> Zip(const vector_t<TComponentInA, 4> &a, const vector_t<TComponentInB, 4> &b,
                                  const vector_t<TComponentInC, 4> &c, const vector_t<TComponentInD, 4> &d,
                                  Func<TOut(TComponentInA a, TComponentInB b, TComponentInC c)> func) noexcept
  {
    return vector_t<TOut, 4>(func(a.x, b.x, c.x, d.x), func(a.y, b.y, c.y, d.y), func(a.z, b.z, c.z, d.z),
                             func(a.w, b.w, c.w, d.w));
  }

#pragma endregion Zip

#pragma region Sum

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, 1> &v) noexcept
  {
    return TComponent(v.x);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, 2> &v) noexcept
  {
    return TComponent(v.x + v.y);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, 3> &v) noexcept
  {
    return TComponent(v.x + v.y + v.z);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, 4> &v) noexcept
  {
    return TComponent(v.x + v.y + v.z + v.w);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, 1> &v,
                                      Func<TComponent(TComponent)> func) noexcept
  {
    return TComponent(func(v.x));
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, 2> &v,
                                      Func<TComponent(TComponent)> func) noexcept
  {
    return TComponent(func(v.x) + func(v.y));
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, 3> &v,
                                      Func<TComponent(TComponent)> func) noexcept
  {
    return TComponent(func(v.x) + func(v.y) + func(v.z));
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, 4> &v,
                                      Func<TComponent(TComponent)> func) noexcept
  {
    return TComponent(func(v.x) + func(v.y) + func(v.z) + func(v.w));
  }

#pragma endregion Sum
}