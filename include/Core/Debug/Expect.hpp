#pragma once

/// @brief Macro to assert equality between two values at compile time.
/// @param msg A message describing the assertion.
/// @param a The first value to compare.
/// @param b The second value to compare.
#define KRYS_EXPECT_EQUAL(msg, a, b) static_assert((a) == (b), msg ": NEQUAL")

/// @brief Macro to assert inequality between two values at compile time.
/// @param msg A message describing the assertion.
/// @param a The first value to compare.
/// @param b The second value to compare.
#define KRYS_EXPECT_NOT_EQUAL(msg, a, b) static_assert((a) != (b), msg ": EQUAL")

/// @brief Macro to assert value is at most `max` at compile time.
/// @param msg A message describing the assertion.
/// @param expr The expression to check.
/// @param max The max valid value.
#define KRYS_EXPECT_LESS_THAN(msg, expr, max) static_assert(((expr) <= max), msg ": GREATER")

/// @brief Macro to assert value is at most `min` at compile time.
/// @param msg A message describing the assertion.
/// @param expr The expression to check.
/// @param min The min valid value.
#define KRYS_EXPECT_GREATER_THAN(msg, expr, min) static_assert(((expr) >= min), msg ": LESS")

/// @brief Macro to assert value is between two values at compile time.
/// @param msg A message describing the assertion.
/// @param expr The expression to check.
/// @param min The min valid value.
/// @param max The max valid value.
#define KRYS_EXPECT_IN_RANGE(msg, expr, min, max)                                                            \
  KRYS_EXPECT_GREATER_THAN(msg, expr, min);                                                                  \
  KRYS_EXPECT_LESS_THAN(msg, expr, max)

/// @brief Macro to assert value is equal to a values with a tolerance amount at compile time.
/// @param msg A message describing the assertion.
/// @param expr The expression to check.
/// @param value The max valid value.
/// @param tolerance The tolerance for error. A common value is 1e-6f, the error precision of floats.
#define KRYS_EXPECT_EQUAL_WITH_TOLERANCE(msg, expr, value, tolerance)                                        \
  KRYS_EXPECT_GREATER_THAN(msg, expr, ((value) - tolerance));                                                \
  KRYS_EXPECT_LESS_THAN(msg, expr, ((value) + tolerance))

/// @brief Macro to assert that a value is true at compile time.
/// @param msg A message describing the assertion.
/// @param expr The expression to check.
#define KRYS_EXPECT_TRUE(msg, expr) static_assert((expr), msg ": FALSE")

/// @brief Macro to assert that a value is false at compile time.
/// @param msg A message describing the assertion.
/// @param expr The expression to check.
#define KRYS_EXPECT_FALSE(msg, expr) static_assert(!(expr), msg ": TRUE")
