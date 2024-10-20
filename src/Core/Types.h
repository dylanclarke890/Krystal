#pragma once

#include "Misc/CompilerDetection.h"

#include <cstddef>
#include <memory>
#include <optional>
#include <stdint.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#if defined(KRYS_COMPILER_VISUAL_STUDIO)
  #include <emmintrin.h>
  #include <xmmintrin.h>
#elif defined(KRYS_COMPILER_CLANG) || defined(KRYS_COMPILER_GCC)
  #include <x86intrin.h>
#endif

namespace Krys
{
  typedef int8_t int8;
  typedef int_fast8_t fast_int8;
  typedef int16_t int16;
  typedef int_fast16_t fast_int16;
  typedef int32_t int32;
  typedef int_fast32_t fast_int32;
  typedef int64_t int64;
  typedef int_fast64_t fast_int64;
  typedef uint8_t uint8;
  typedef uint16_t uint16;
  typedef uint32_t uint32;
  typedef uint64_t uint64;
  typedef uint_fast8_t fast_uint8;
  typedef uint_fast16_t fast_uint16;
  typedef uint_fast32_t fast_uint32;
  typedef uint_fast64_t fast_uint64;

  typedef unsigned char uchar;
  typedef unsigned short ushort;
  typedef unsigned int uint;
  typedef unsigned long ulong;

  typedef std::byte byte;
  typedef float float32;
  typedef double float64;

  typedef __m128 simd_float;
  typedef __m128i simd_int;
  typedef __m128d simd_double;

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

  template <typename T>
  using WeakRef = std::weak_ptr<T>;

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

#define NO_DISCARD [[nodiscard]]
}