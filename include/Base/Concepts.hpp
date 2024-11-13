#include <concepts>
#include <type_traits>

namespace Krys
{
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
}
