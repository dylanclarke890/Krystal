#pragma once

#if defined(_MSC_VER)
  #define KRYS_COMPILER_VISUAL_STUDIO
#elif defined(__clang__)
  #define KRYS_COMPILER_CLANG
#elif defined(__GNUC__)
  #define KRYS_COMPILER_GCC
#else
  #error "Unknown Compiler!"
#endif