#pragma once

#include <memory>
#include <optional>
#include <stdint.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <cstddef>

namespace Krys
{
  typedef std::byte byte;
  typedef int8_t int8;
  typedef int16_t int16;
  typedef int32_t int32;
  typedef int64_t int64;

  typedef float float32;
  typedef double float64;

  typedef unsigned char uchar;
  typedef unsigned short ushort;
  typedef unsigned int uint;
  typedef uint8_t uint8;
  typedef uint16_t uint16;
  typedef uint32_t uint32;
  typedef uint64_t uint64;

  typedef std::string string;
  typedef std::string_view stringview;

  template <typename T>
  using Nullable = std::optional<T>;

  template <typename TKey, typename TValue, typename TKeyHasher = std::hash<TKey>>
  using Map = std::unordered_map<TKey, TValue, TKeyHasher>;

  template <typename T>
  using List = std::vector<T>;

  template <typename T>
  using Unique = std::unique_ptr<T>;

  template <typename T>
  using Ref = std::shared_ptr<T>;

  template <typename T, typename... Args>
  constexpr Unique<T> CreateUnique(Args &&...args)
  {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  template <typename T, typename... Args>
  constexpr Ref<T> CreateRef(Args &&...args)
  {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
}