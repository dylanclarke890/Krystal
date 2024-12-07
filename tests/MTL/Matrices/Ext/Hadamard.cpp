#include "MTL/Matrices/Ext/Hadamard.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat2x3.hpp"
#include "MTL/Matrices/Mat2x4.hpp"
#include "MTL/Matrices/Mat3x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x2.hpp"
#include "MTL/Matrices/Mat4x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Mat2x2_Hadamard()
  {
    using mat_t = Mat2x2;
    constexpr mat_t a {1, 2, 3, 4};
    constexpr mat_t b {5, 6, 7, 8};
    constexpr mat_t result {5, 12, 21, 32};
    KRYS_EXPECT_EQUAL("Hadamard Mat2x2", Hadamard(a, b), result);
  }

  static void Test_Mat2x3_Hadamard()
  {
    using mat_t = Mat2x3;
    constexpr mat_t a {1, 2, 3, 4, -2, 3};
    constexpr mat_t b {5, 6, 7, 8, 3, -2};
    constexpr mat_t result {5, 12, 21, 32, -6, -6};
    KRYS_EXPECT_EQUAL("Hadamard Mat2x3", Hadamard(a, b), result);
  }

  static void Test_Mat2x4_Hadamard()
  {
    using mat_t = Mat2x4;
    constexpr mat_t a {1, 2, 3, 4, -2, 3, 0, 5};
    constexpr mat_t b {5, 6, 7, 8, 3, -2, 4, 1};
    constexpr mat_t result {5, 12, 21, 32, -6, -6, 0, 5};
    KRYS_EXPECT_EQUAL("Hadamard Mat2x4", Hadamard(a, b), result);
  }

  static void Test_Mat3x2_Hadamard()
  {
    using mat_t = Mat3x2;
    constexpr mat_t a {1, 2, 3, 4, -2, 3};
    constexpr mat_t b {5, 6, 7, 8, 3, -2};
    constexpr mat_t result {5, 12, 21, 32, -6, -6};
    KRYS_EXPECT_EQUAL("Hadamard Mat3x2", Hadamard(a, b), result);
  }

  static void Test_Mat3x3_Hadamard()
  {
    using mat_t = Mat3x3;
    constexpr mat_t a {1, 2, 3, 4, 5, 6, 7, 8, 9};
    constexpr mat_t b {9, 8, 7, 6, 5, 4, 3, 2, 1};
    constexpr mat_t result {9, 16, 21, 24, 25, 24, 21, 16, 9};
    KRYS_EXPECT_EQUAL("Hadamard Mat3x3", Hadamard(a, b), result);
  }

  static void Test_Mat3x4_Hadamard()
  {
    using mat_t = Mat3x4;
    constexpr mat_t a {1, 2, 3, 4, 5, 6, 7, 8, -1, -2, -3, -4};
    constexpr mat_t b {4, 3, 2, 1, -1, -2, -3, -4, 1, 2, 3, 4};
    constexpr mat_t result {4, 6, 6, 4, -5, -12, -21, -32, -1, -4, -9, -16};
    KRYS_EXPECT_EQUAL("Hadamard Mat3x4", Hadamard(a, b), result);
  }

  static void Test_Mat4x2_Hadamard()
  {
    using mat_t = Mat4x2;
    constexpr mat_t a {1, 2, 3, 4, -2, 3, 0, 5};
    constexpr mat_t b {5, 6, 7, 8, 3, -2, 4, 1};
    constexpr mat_t result {5, 12, 21, 32, -6, -6, 0, 5};
    KRYS_EXPECT_EQUAL("Hadamard Mat4x2", Hadamard(a, b), result);
  }

  static void Test_Mat4x3_Hadamard()
  {
    using mat_t = Mat4x3;
    constexpr mat_t a {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    constexpr mat_t b {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    constexpr mat_t result {12, 22, 30, 36, 40, 42, 42, 40, 36, 30, 22, 12};
    KRYS_EXPECT_EQUAL("Hadamard Mat4x3", Hadamard(a, b), result);
  }

  static void Test_Mat4x4_Hadamard()
  {
    using mat_t = Mat4x4;
    constexpr mat_t a {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    constexpr mat_t b {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    constexpr mat_t result {16, 30, 42, 52, 60, 66, 70, 72, 72, 70, 66, 60, 52, 42, 30, 16};
    KRYS_EXPECT_EQUAL("Hadamard Mat4x4", Hadamard(a, b), result);
  }
}
