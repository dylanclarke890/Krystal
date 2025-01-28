#pragma once

namespace Krys
{
#define VA_ARGS(...) , ##__VA_ARGS__
#define CONCATENATE_DETAIL(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_DETAIL(x, y)

#ifdef __INTELLISENSE__
  /// @brief Intellisense sometimes loses when parsing code with require statements.
  /// This macro hides them from intellisense while ensuring they are included when actually compiling.
  #define REQUIRES(x)
#else
  #define REQUIRES(x) requires(x)
#endif

// Resolve the best macro for a function signature, based on the compiler being used.
// Note: only gets resolved during preprocessing so your code editor may highlight the wrong one (i.e the
// 'else' branch) but should still work.
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000))                                     \
  || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
  #define KRYS_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
  #define KRYS_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__) || defined(_MSC_VER)
  #define KRYS_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
  #define KRYS_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
  #define KRYS_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199'901)
  #define KRYS_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201'103)
  #define KRYS_FUNC_SIG __func__
#else
  #error "KRYS_FUNC_SIG unknown!"
#endif

// Compiler-specific macros for disabling and restoring warnings
#if defined(_MSC_VER) // Microsoft Visual C++
  #define KRYS_DISABLE_WARNING_PUSH() __pragma(warning(push))
  #define KRYS_DISABLE_WARNING_POP() __pragma(warning(pop))
  #define KRYS_DISABLE_WARNING(msvcWarningCode, gccWarningName) __pragma(warning(disable : msvcWarningCode))
#elif defined(__GNUC__) || defined(__clang__) // GCC or Clang
  #define KRYS_DISABLE_WARNING_PUSH() _Pragma("GCC diagnostic push")
  #define KRYS_DISABLE_WARNING_POP() _Pragma("GCC diagnostic pop")
  #if defined(__clang__)
    #define KRYS_DISABLE_WARNING(msvcWarningCode, gccWarningName)                                            \
      _Pragma("clang diagnostic ignored \"" gccWarningName "\"")
  #else
    #define KRYS_DISABLE_WARNING(msvcWarningCode, gccWarningName)                                            \
      _Pragma("GCC diagnostic ignored \"" gccWarningName "\"")
  #endif
#else
  #define KRYS_DISABLE_WARNING_PUSH()
  #define KRYS_DISABLE_WARNING_POP()
  #define KRYS_DISABLE_WARNING(msvcWarningCode, gccWarningName)
#endif

/// @brief Disables copying for the given class.
#define NO_COPY(Class)                                                                                       \
  Class(const Class &) = delete;                                                                             \
  Class &operator=(const Class &) = delete;

/// @brief Disables moving for the given class.
#define NO_MOVE(Class)                                                                                       \
  Class(Class &&) = delete;                                                                                  \
  Class &operator=(Class &&) = delete;

#define NO_COPY_MOVE(Class)                                                                                  \
  NO_COPY(Class)                                                                                             \
  NO_MOVE(Class)

#define STATIC_CLASS(Class)                                                                                  \
  NO_COPY_MOVE(Class)                                                                                        \
  Class() = delete;

/// @brief Defines bitwise operators for an enum class.
/// @param EnumClass The enum class to define the operators for.
/// @param type The underlying type of the enum (e.g., unsigned short).
#define ENUM_CLASS_BITWISE_OPERATORS(EnumClass, type)                                                        \
  inline constexpr EnumClass operator|(EnumClass a, EnumClass b)                                             \
  {                                                                                                          \
    return static_cast<EnumClass>(static_cast<type>(a) | static_cast<type>(b));                              \
  }                                                                                                          \
                                                                                                             \
  inline constexpr EnumClass operator&(EnumClass a, EnumClass b)                                             \
  {                                                                                                          \
    return static_cast<EnumClass>(static_cast<type>(a) & static_cast<type>(b));                              \
  }                                                                                                          \
                                                                                                             \
  inline constexpr EnumClass operator^(EnumClass a, EnumClass b)                                             \
  {                                                                                                          \
    return static_cast<EnumClass>(static_cast<type>(a) ^ static_cast<type>(b));                              \
  }                                                                                                          \
                                                                                                             \
  inline constexpr EnumClass operator~(EnumClass a)                                                          \
  {                                                                                                          \
    return static_cast<EnumClass>(~static_cast<type>(a));                                                    \
  }                                                                                                          \
                                                                                                             \
  inline EnumClass &operator|=(EnumClass &a, EnumClass b)                                                    \
  {                                                                                                          \
    return a = a | b;                                                                                        \
  }                                                                                                          \
                                                                                                             \
  inline EnumClass &operator&=(EnumClass &a, EnumClass b)                                                    \
  {                                                                                                          \
    return a = a & b;                                                                                        \
  }                                                                                                          \
                                                                                                             \
  inline EnumClass &operator^=(EnumClass &a, EnumClass b)                                                    \
  {                                                                                                          \
    return a = a ^ b;                                                                                        \
  }
}