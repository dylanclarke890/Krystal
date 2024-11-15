#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr void ForEach(const vector_t<TComponent, Length> &v, Func<void(TComponent v)> func) noexcept;

  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr vector_t<TComponent, Length> Map(const vector_t<TComponent, Length> &v,
                                             Func<TComponent(TComponent v)> func) noexcept;

  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, Length> &v) noexcept;

  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD TComponent Sum(const vector_t<TComponent, Length> &v,
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

  template <IsArithmeticT TComponent>
  constexpr vector_t<TComponent, 1> Map(const vector_t<TComponent, 1> &v,
                                        Func<TComponent(TComponent)> func) noexcept
  {
    return vector_t<TComponent, 1>(func(v.x));
  }

  template <IsArithmeticT TComponent>
  constexpr vector_t<TComponent, 2> Map(const vector_t<TComponent, 2> &v,
                                        Func<TComponent(TComponent)> func) noexcept
  {
    return vector_t<TComponent, 2>(func(v.x), func(v.y));
  }

  template <IsArithmeticT TComponent>
  constexpr vector_t<TComponent, 3> Map(const vector_t<TComponent, 3> &v,
                                        Func<TComponent(TComponent)> func) noexcept
  {
    return vector_t<TComponent, 3>(func(v.x), func(v.y), func(v.z));
  }

  template <IsArithmeticT TComponent>
  constexpr vector_t<TComponent, 4> Map(const vector_t<TComponent, 4> &v,
                                        Func<TComponent(TComponent)> func) noexcept
  {
    return vector_t<TComponent, 4>(func(v.x), func(v.y), func(v.z), func(v.w));
  }

#pragma endregion Map

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