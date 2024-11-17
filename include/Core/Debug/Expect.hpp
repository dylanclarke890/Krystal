#pragma once

/// @brief Macro to assert equality between two values at compile time.
/// @param msg A message describing the assertion.
/// @param a The first value to compare.
/// @param b The second value to compare.
#define KRYS_EXPECT_EQUAL(msg, a, b) static_assert((a) == (b), msg " failed: Values are not equal.")

/// @brief Macro to assert inequality between two values at compile time.
/// @param msg A message describing the assertion.
/// @param a The first value to compare.
/// @param b The second value to compare.
#define KRYS_EXPECT_NOT_EQUAL(msg, a, b) static_assert((a) != (b), msg " failed: Values are equal.")

/// @brief Macro to assert that a value is true at compile time.
/// @param msg A message describing the assertion.
/// @param expr The expression to check.
#define KRYS_EXPECT_TRUE(msg, expr) static_assert((expr), msg " failed: evaluated to false.")

/// @brief Macro to assert that a value is false at compile time.
/// @param msg A message describing the assertion.
/// @param expr The expression to check.
#define KRYS_EXPECT_FALSE(msg, expr) static_assert(!(expr), msg " failed: evaluated to true.")
