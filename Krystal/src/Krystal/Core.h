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

#define BIT(x) 1 << x