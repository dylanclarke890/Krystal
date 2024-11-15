#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Vectors/Base.hpp"

namespace Krys::MTL
{
  /// @brief Performs a component-wise `<` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `Length` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<bool, Length> LessThan(const vector_t<TComponent, Length> &a,
                                                       const vector_t<TComponent, Length> &b) noexcept;

  /// @brief Performs a component-wise `<=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `Length` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<bool, Length> LessThanOrEqual(const vector_t<TComponent, Length> &a,
                                                              const vector_t<TComponent, Length> &b) noexcept;

  /// @brief Performs a component-wise `==` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `Length` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<bool, Length> Equal(const vector_t<TComponent, Length> &a,
                                                    const vector_t<TComponent, Length> &b) noexcept;

  /// @brief Performs a component-wise `!=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `Length` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<bool, Length> NotEqual(const vector_t<TComponent, Length> &a,
                                                       const vector_t<TComponent, Length> &b) noexcept;

  /// @brief Performs a component-wise `>` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `Length` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<bool, Length> GreaterThan(const vector_t<TComponent, Length> &a,
                                                          const vector_t<TComponent, Length> &b) noexcept;

  /// @brief Performs a component-wise `>=` comparison between `a` and `b`.
  /// @tparam TComponent The underlying arithmetic type of the vector.
  /// @tparam Length The size of the vector.
  /// @param a Left operand.
  /// @param b Right operand.
  /// @return A `Length` size bool vector where each component represents the result of the comparison.
  template <IsArithmeticT TComponent, vec_length_t Length>
  constexpr NO_DISCARD vector_t<bool, Length>
    GreaterThanOrEqual(const vector_t<TComponent, Length> &a, const vector_t<TComponent, Length> &b) noexcept;

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

#pragma region LessThan

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 1> LessThan(const vector_t<TComponent, 1> &a,
                                                  const vector_t<TComponent, 1> &b) noexcept
  {
    return vector_t<bool, 1>(a.x < b.x);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 2> LessThan(const vector_t<TComponent, 2> &a,
                                                  const vector_t<TComponent, 2> &b) noexcept
  {
    return vector_t<bool, 2>(a.x < b.x, a.y < b.y);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 3> LessThan(const vector_t<TComponent, 3> &a,
                                                  const vector_t<TComponent, 3> &b) noexcept
  {
    return vector_t<bool, 3>(a.x < b.x, a.y < b.y, a.z < b.z);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 4> LessThan(const vector_t<TComponent, 4> &a,
                                                  const vector_t<TComponent, 4> &b) noexcept
  {
    return vector_t<bool, 4>(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
  }

#pragma endregion LessThan

#pragma region LessThanOrEqual

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 1> LessThanOrEqual(const vector_t<TComponent, 1> &a,
                                                         const vector_t<TComponent, 1> &b) noexcept
  {
    return vector_t<bool, 1>(a.x <= b.x);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 2> LessThanOrEqual(const vector_t<TComponent, 2> &a,
                                                         const vector_t<TComponent, 2> &b) noexcept
  {
    return vector_t<bool, 2>(a.x <= b.x, a.y <= b.y);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 3> LessThanOrEqual(const vector_t<TComponent, 3> &a,
                                                         const vector_t<TComponent, 3> &b) noexcept
  {
    return vector_t<bool, 3>(a.x <= b.x, a.y <= b.y, a.z <= b.z);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 4> LessThanOrEqual(const vector_t<TComponent, 4> &a,
                                                         const vector_t<TComponent, 4> &b) noexcept
  {
    return vector_t<bool, 4>(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
  }

#pragma endregion LessThanOrEqual

#pragma region Equal

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 1> Equal(const vector_t<TComponent, 1> &a,
                                               const vector_t<TComponent, 1> &b) noexcept
  {
    return vector_t<bool, 1>(a.x == b.x);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 2> Equal(const vector_t<TComponent, 2> &a,
                                               const vector_t<TComponent, 2> &b) noexcept
  {
    return vector_t<bool, 2>(a.x == b.x, a.y == b.y);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 3> Equal(const vector_t<TComponent, 3> &a,
                                               const vector_t<TComponent, 3> &b) noexcept
  {
    return vector_t<bool, 3>(a.x == b.x, a.y == b.y, a.z == b.z);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 4> Equal(const vector_t<TComponent, 4> &a,
                                               const vector_t<TComponent, 4> &b) noexcept
  {
    return vector_t<bool, 4>(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
  }

#pragma endregion NotEqual

#pragma region NotEqual

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 1> NotEqual(const vector_t<TComponent, 1> &a,
                                                  const vector_t<TComponent, 1> &b) noexcept
  {
    return vector_t<bool, 1>(a.x != b.x);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 2> NotEqual(const vector_t<TComponent, 2> &a,
                                                  const vector_t<TComponent, 2> &b) noexcept
  {
    return vector_t<bool, 2>(a.x != b.x, a.y != b.y);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 3> NotEqual(const vector_t<TComponent, 3> &a,
                                                  const vector_t<TComponent, 3> &b) noexcept
  {
    return vector_t<bool, 3>(a.x != b.x, a.y != b.y, a.z != b.z);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 4> NotEqual(const vector_t<TComponent, 4> &a,
                                                  const vector_t<TComponent, 4> &b) noexcept
  {
    return vector_t<bool, 4>(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
  }

#pragma endregion NotEqual

#pragma region GreaterThan

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 1> GreaterThan(const vector_t<TComponent, 1> &a,
                                                     const vector_t<TComponent, 1> &b) noexcept
  {
    return vector_t<bool, 1>(a.x > b.x);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 2> GreaterThan(const vector_t<TComponent, 2> &a,
                                                     const vector_t<TComponent, 2> &b) noexcept
  {
    return vector_t<bool, 2>(a.x > b.x, a.y > b.y);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 3> GreaterThan(const vector_t<TComponent, 3> &a,
                                                     const vector_t<TComponent, 3> &b) noexcept
  {
    return vector_t<bool, 3>(a.x > b.x, a.y > b.y, a.z > b.z);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 4> GreaterThan(const vector_t<TComponent, 4> &a,
                                                     const vector_t<TComponent, 4> &b) noexcept
  {
    return vector_t<bool, 4>(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
  }

#pragma endregion GreaterThan

#pragma region GreaterThanOrEqual

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 1> GreaterThanOrEqual(const vector_t<TComponent, 1> &a,
                                                            const vector_t<TComponent, 1> &b) noexcept
  {
    return vector_t<bool, 1>(a.x >= b.x);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 2> GreaterThanOrEqual(const vector_t<TComponent, 2> &a,
                                                            const vector_t<TComponent, 2> &b) noexcept
  {
    return vector_t<bool, 2>(a.x >= b.x, a.y >= b.y);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 3> GreaterThanOrEqual(const vector_t<TComponent, 3> &a,
                                                            const vector_t<TComponent, 3> &b) noexcept
  {
    return vector_t<bool, 3>(a.x >= b.x, a.y >= b.y, a.z >= b.z);
  }

  template <IsArithmeticT TComponent>
  constexpr NO_DISCARD vector_t<bool, 4> GreaterThanOrEqual(const vector_t<TComponent, 4> &a,
                                                            const vector_t<TComponent, 4> &b) noexcept
  {
    return vector_t<bool, 4>(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
  }

#pragma endregion GreaterThanOrEqual

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