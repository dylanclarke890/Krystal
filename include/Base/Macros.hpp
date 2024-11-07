#pragma once

namespace Krys
{
/// @brief Define bitwise operators for an enum class.
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

/// @brief Deletes copy and assign constructors for the given class.
#define NO_COPY_AND_ASSIGN(Class)                                                                            \
  Class(const Class &) = delete;                                                                             \
  Class &operator=(const Class &) = delete;
}