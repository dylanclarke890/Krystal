#pragma once

#include <memory>

#ifdef KRYS_PLATFORM_WINDOWS
  #ifdef KRYS_DYNAMIC_LINK
    #ifdef KRYS_BUILD_DLL
      #define KRYSTAL_API __declspec(dllexport)
    #else
      #define KRYSTAL_API __declspec(dllimport)
    #endif
  #else
    #define KRYSTAL_API
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

#define KRYS_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Krys
{
  template<typename T>
  using Scope = std::unique_ptr<T>;
 
  template<typename T>
  using Ref = std::shared_ptr<T>;
}