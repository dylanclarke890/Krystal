#pragma once

#include <concepts>
#include <type_traits>

namespace Krys
{
  /// @brief Checks type `T` is an integral type.
  template <typename T>
  concept IsIntegralT = std::is_integral_v<T>;

  /// @brief Checks type `T` is an unsigned type.
  template <typename T>
  concept IsUnsignedT = std::is_unsigned_v<T>;

  /// @brief Checks type `T` is a signed type.
  template <typename T>
  concept IsSignedT = std::is_signed_v<T>;

  /// @brief Checks type `T` is a floating point type.
  template <typename T>
  concept IsFloatingPointT = std::is_floating_point_v<T>;

  /// @brief Checks type `T` is an arithmetic type (built-in numeric type).
  template <typename T>
  concept IsArithmeticT = std::is_arithmetic_v<T>;

  /// @brief Checks type `T` is copyable.
  template <typename T>
  concept IsCopyableT = std::copyable<T>;

  /// @brief Checks type `TA` can be assigned to type `TB`.
  template <typename TA, typename TB>
  concept IsAssignableT = std::is_assignable_v<TA, TB>;

  /// @brief Checks type `T` is comparable.
  template <typename T>
  concept IsComparableT = std::equality_comparable<T>;

  /// @brief Checks if type `TA` supports addition and compound addition with type `TB`.
  template <typename TA, typename TB>
  concept IsAddableT = requires(TA a, TB b) {
    { a + b } -> std::same_as<TA>;
    { a += b } -> std::same_as<TA &>;
  };

  /// @brief Checks if type `TA` supports subtraction and compound subtraction with type `TB`.
  template <typename TA, typename TB>
  concept IsSubtractableT = requires(TA a, TB b) {
    { a - b } -> std::same_as<TA>;
    { a -= b } -> std::same_as<TA &>;
  };

  /// @brief Checks if type `TA` supports division and compound division with type `TB`.
  template <typename TA, typename TB>
  concept IsDivisibleT = requires(TA a, TB b) {
    { a / b } -> std::same_as<TA>;
    { a /= b } -> std::same_as<TA &>;
  };

  /// @brief Checks if type `TA` supports multiplication and compound multiplication with type `TB`.
  template <typename TA, typename TB>
  concept IsMultipliableT = requires(TA a, TB b) {
    { a *b } -> std::same_as<TA>;
    { a *= b } -> std::same_as<TA &>;
  };

  /// @brief Checks if type `T` supports unary negation.
  template <typename T>
  concept IsNegatableT = requires(T a) {
    { -a } -> std::same_as<T>;
  };

  /// @brief Checks if type `TA` supports all maths operations with `TB`.
  template <typename TA, typename TB>
  concept SupportsArithmeticOperations =
    IsAddableT<TA, TB> && IsSubtractableT<TA, TB> && IsDivisibleT<TA, TB> && IsMultipliableT<TA, TB>;

/// @brief Determines if the current code is being evaluated in a compile-time context.
/// @returns `true` if the current context is a compile-time evaluation; otherwise `false`.
/// @example
/// constexpr int Foo() {
///   KRYS_IF_COMPILE_CONTEXT {
///     return 42; // Compile-time specific logic
///   }
///   return 0; // Runtime fallback
/// }
#define KRYS_IF_COMPILE_CONTEXT if constexpr(std::is_constant_evaluated())

/// @brief Determines if the current code will be evaluated at runtime.
/// @returns `true` if the current context is a runtime evaluation; otherwise `false`.
/// @example
/// constexpr int Bar() {
///   KRYS_IF_RUNTIME_CONTEXT {
///     return 42; // Runtime specific logic
///   }
///   return 0; // Compile-time fallback
/// }
#define KRYS_IF_RUNTIME_CONTEXT if constexpr(!std::is_constant_evaluated())
}
