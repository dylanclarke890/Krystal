#pragma once

#include <array>
#include <functional>
#include <optional>
#include <queue>
#include <set>
#include <stdint.h>
#include <string>
#include <string_view>
#include <initializer_list>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <expected>

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

  using std::declval;
  using std::initializer_list;

  template <typename T>
  using Nullable = std::optional<T>;

  template <typename TKey, typename TValue, typename TKeyHasher = std::hash<TKey>>
  using Map = std::unordered_map<TKey, TValue, TKeyHasher>;

  template <typename T, size_t size>
  using Array = std::array<T, size>;

  template <typename T>
  using List = std::vector<T>;

  template <typename T>
  using LinkedList = std::list<T>;

  template <typename T>
  using Queue = std::queue<T>;

  template <typename T>
  using Set = std::set<T>;

  template <typename T>
  using Func = std::function<T>;

  template <typename T, typename ErrorType = string>
  using Expected = std::expected<T, ErrorType>;

  template <typename T>
  using Unexpected = std::unexpected<T>;
}