#pragma once

#include <array>
#include <functional>
#include <optional>
#include <queue>
#include <set>
#include <stdint.h>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace Krys
{
  typedef unsigned char uchar;
  typedef unsigned short ushort;
  typedef unsigned long ulong;

  typedef int8_t int8;
  typedef int16_t int16;
  typedef int32_t int32;
  typedef int64_t int64;
  typedef int_fast64_t fast_int64;
  typedef int_fast8_t fast_int8;
  typedef int_fast16_t fast_int16;
  typedef int_fast32_t fast_int32;

  typedef unsigned int uint;
  typedef uint8_t uint8;
  typedef uint16_t uint16;
  typedef uint32_t uint32;
  typedef uint64_t uint64;
  typedef uint_fast8_t fast_uint8;
  typedef uint_fast16_t fast_uint16;
  typedef uint_fast32_t fast_uint32;
  typedef uint_fast64_t fast_uint64;

  typedef std::byte byte;
  typedef float float32;
  typedef double float64;

  typedef std::string string;
  typedef std::string_view stringview;

  template <typename T>
  using Nullable = std::optional<T>;

  template <typename TKey, typename TValue, typename TKeyHasher = std::hash<TKey>>
  using Map = std::unordered_map<TKey, TValue, TKeyHasher>;

  template <typename T, size_t size>
  using Array = std::array<T, size>;

  template <typename T>
  using List = std::vector<T>;

  template <typename T>
  using Queue = std::queue<T>;

  template <typename T>
  using Set = std::set<T>;

  template <typename T>
  using Func = std::function<T>;

  template <typename T>
  concept IsArithmeticT = std::is_arithmetic_v<T>;

  template <typename T>
  concept IsCopyableT = std::copyable<T>;

  template <typename TVector, typename TComponent>
  concept IVector =
    IsCopyableT<TVector> && IsArithmeticT<TComponent> && requires(TVector vec, TComponent scalar) {
      // Assignment
      { vec = vec } -> std::same_as<TVector &>;

      // Equality
      { vec == vec } -> std::same_as<bool>;
      { vec != vec } -> std::same_as<bool>;

      // Addition
      { vec + vec } -> std::same_as<TVector>;
      { vec += vec } -> std::same_as<TVector &>;
      { vec + scalar } -> std::same_as<TVector>;
      { vec += scalar } -> std::same_as<TVector &>;

      // Subtraction
      { vec - vec } -> std::same_as<TVector>;
      { vec -= vec } -> std::same_as<TVector &>;
      { vec - scalar } -> std::same_as<TVector>;
      { vec -= scalar } -> std::same_as<TVector &>;

      // Division
      { vec / vec } -> std::same_as<TVector>;
      { vec /= vec } -> std::same_as<TVector &>;
      { vec / scalar } -> std::same_as<TVector>;
      { vec /= scalar } -> std::same_as<TVector &>;

      // Multiplication
      { vec *vec } -> std::same_as<TVector>;
      { vec *= vec } -> std::same_as<TVector &>;
      { vec *scalar } -> std::same_as<TVector>;
      { vec *= scalar } -> std::same_as<TVector &>;

      // Unary operators
      { -vec } -> std::same_as<TVector>;
      { +vec } -> std::same_as<TVector>;
    };
}