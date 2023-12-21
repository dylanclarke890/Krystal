#pragma once

#ifdef KRYS_PLATFORM_WINDOWS
  #ifdef KRYS_BUILD_DLL
    #define KRYSTAL_API __declspec(dllexport)
  #else
    #define KRYSTAL_API __declspec(dllimport)
  #endif
#else
  #error Krystal only supports Windows!
#endif

#define BIT(x) (1 << x)

#ifdef KRYS_ENABLE_ASSERTS
  #define KRYS_ASSERT(x, ...) { if(!(x)) { KRYS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
  #define KRYS_CORE_ASSERT(x, ...) { if(!(x)) { KRYS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
  #define KRYS_ASSERT(x, ...)
  #define KRYS_CORE_ASSERT(x, ...)
#endif