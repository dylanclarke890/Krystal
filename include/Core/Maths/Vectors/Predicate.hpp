#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Checks if any of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The vector to check.
  /// @returns True if any of the components satified the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr bool AnyOf(const vector_t<TComponent, Length> &v, Func<bool(TComponent)> predicate) noexcept;

  /// @brief Checks if all of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The vector to check.
  /// @returns True if all of the components satified the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr bool AllOf(const vector_t<TComponent, Length> &v, Func<bool(TComponent)> predicate) noexcept;

  /// @brief Checks if none of the components in `v` satisfy the predicate.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param v The vector to check.
  /// @returns True if none of the components satified the predicate, false otherwise.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr bool NoneOf(const vector_t<TComponent, Length> &v, Func<bool(TComponent)> predicate) noexcept;

#pragma region AnyOf

  template <IsArithmeticT TComponent>
  constexpr bool AnyOf(const vector_t<TComponent, 1> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v.x);
  }

  template <IsArithmeticT TComponent>
  constexpr bool AnyOf(const vector_t<TComponent, 2> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v.x) || predicate(v.y);
  }

  template <IsArithmeticT TComponent>
  constexpr bool AnyOf(const vector_t<TComponent, 3> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v.x) || predicate(v.y) || predicate(v.z);
  }

  template <IsArithmeticT TComponent>
  constexpr bool AnyOf(const vector_t<TComponent, 4> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v.x) || predicate(v.y) || predicate(v.z) || predicate(v.w);
  }

#pragma endregion AnyOf

#pragma region AllOf

  template <IsArithmeticT TComponent>
  constexpr bool AllOf(const vector_t<TComponent, 1> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v.x);
  }

  template <IsArithmeticT TComponent>
  constexpr bool AllOf(const vector_t<TComponent, 2> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v.x) && predicate(v.y);
  }

  template <IsArithmeticT TComponent>
  constexpr bool AllOf(const vector_t<TComponent, 3> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v.x) && predicate(v.y) && predicate(v.z);
  }

  template <IsArithmeticT TComponent>
  constexpr bool AllOf(const vector_t<TComponent, 4> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return predicate(v.x) && predicate(v.y) && predicate(v.z) && predicate(v.w);
  }

#pragma endregion AllOf

#pragma region NoneOf

  template <IsArithmeticT TComponent>
  constexpr bool NoneOf(const vector_t<TComponent, 1> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return !predicate(v.x);
  }

  template <IsArithmeticT TComponent>
  constexpr bool NoneOf(const vector_t<TComponent, 2> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return !predicate(v.x) && !predicate(v.y);
  }

  template <IsArithmeticT TComponent>
  constexpr bool NoneOf(const vector_t<TComponent, 3> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return !predicate(v.x) && !predicate(v.y) && !predicate(v.z);
  }

  template <IsArithmeticT TComponent>
  constexpr bool NoneOf(const vector_t<TComponent, 4> &v, Func<bool(TComponent)> predicate) noexcept
  {
    return !predicate(v.x) && !predicate(v.y) && !predicate(v.z) && !predicate(v.w);
  }

#pragma endregion NoneOf
}