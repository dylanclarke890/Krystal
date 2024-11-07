#pragma once

#include "Base/Detection.hpp"

#if defined(KRYS_COMPILER_VISUAL_STUDIO)
  #include <emmintrin.h>
  #include <xmmintrin.h>
#elif defined(KRYS_COMPILER_CLANG) || defined(KRYS_COMPILER_GCC)
  #include <x86intrin.h>
#endif

namespace Krys
{
  typedef __m128 simd_float;
  typedef __m128i simd_int;
  typedef __m128d simd_double;
}