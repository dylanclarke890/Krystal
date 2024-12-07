#include "MTL/Matrices/Ext/Mod.hpp"
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

  static void Test_Mat2x2_Mod()
  {
    using mat_t = Mat2x2;
    constexpr mat_t mat {10, -20, 30, -40};
    KRYS_EXPECT_EQUAL("Mod Mat2x2", Mod(mat, mat_t(7, 5, 6, 3)), mat_t(3, 0, 0, -1));
  }

  static void Test_Mat2x3_Mod()
  {
    using mat_t = Mat2x3;
    constexpr mat_t mat {10, -20, 30, -40, 50, -60};
    constexpr mat_t modMat {7, 5, 6, 3, 8, 4};
    constexpr mat_t result {3, 0, 0, -1, 2, 0};
    KRYS_EXPECT_EQUAL("Mod Mat2x3", Mod(mat, modMat), result);
  }

  static void Test_Mat2x4_Mod()
  {
    using mat_t = Mat2x4;
    constexpr mat_t mat {10, -20, 30, -40, 50, -60, 70, -80};
    constexpr mat_t modMat {7, 5, 6, 3, 8, 4, 9, 10};
    constexpr mat_t result {3, 0, 0, -1, 2, 0, 7, 0};
    KRYS_EXPECT_EQUAL("Mod Mat2x4", Mod(mat, modMat), result);
  }

  static void Test_Mat3x2_Mod()
  {
    using mat_t = Mat3x2;
    constexpr mat_t mat {10, -20, 30, -40, 50, -60};
    constexpr mat_t modMat {7, 5, 6, 3, 8, 4};
    constexpr mat_t result {3, 0, 0, -1, 2, 0};
    KRYS_EXPECT_EQUAL("Mod Mat3x2", Mod(mat, modMat), result);
  }

  static void Test_Mat3x3_Mod()
  {
    using mat_t = Mat3x3;
    constexpr mat_t mat {10, -20, 30, -40, 50, -60, 70, -80, 90};
    constexpr mat_t modMat {7, 5, 6, 3, 8, 4, 9, 10, 11};
    constexpr mat_t result {3, 0, 0, -1, 2, 0, 7, 0, 2};
    KRYS_EXPECT_EQUAL("Mod Mat3x3", Mod(mat, modMat), result);
  }

  static void Test_Mat3x4_Mod()
  {
    using mat_t = Mat3x4;
    constexpr mat_t mat {10, -20, 30, -40, 50, -60, 70, -80, 90, 100, 110, 120};
    constexpr mat_t modMat {7, 5, 6, 3, 8, 4, 9, 10, 11, 12, 13, 14};
    constexpr mat_t result {3, 0, 0, -1, 2, 0, 7, 0, 2, 4, 6, 8};
    KRYS_EXPECT_EQUAL("Mod Mat3x4", Mod(mat, modMat), result);
  }

  static void Test_Mat4x2_Mod()
  {
    using mat_t = Mat4x2;
    constexpr mat_t mat {10, -20, 30, -40, 50, -60, 70, -80};
    constexpr mat_t modMat {7, 5, 6, 3, 8, 4, 9, 10};
    constexpr mat_t result {3, 0, 0, -1, 2, 0, 7, 0};
    KRYS_EXPECT_EQUAL("Mod Mat4x2", Mod(mat, modMat), result);
  }

  static void Test_Mat4x3_Mod()
  {
    using mat_t = Mat4x3;
    constexpr mat_t mat {10, -20, 30, -40, 50, -60, 70, -80, 90, 100, 110, 120};
    constexpr mat_t modMat {7, 5, 6, 3, 8, 4, 9, 10, 11, 12, 13, 14};
    constexpr mat_t result {3, 0, 0, -1, 2, 0, 7, 0, 2, 4, 6, 8};
    KRYS_EXPECT_EQUAL("Mod Mat4x3", Mod(mat, modMat), result);
  }

  static void Test_Mat4x4_Mod()
  {
    using mat_t = Mat4x4;
    constexpr mat_t mat {10, -20, 30, -40, 50, -60, 70, -80, 90, 100, 110, 120, 130, 140, 150, 160};
    constexpr mat_t modMat {7, 5, 6, 3, 8, 4, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    constexpr mat_t result {3, 0, 0, -1, 2, 0, 7, 0, 2, 4, 6, 8, 10, 12, 14, 16};
    KRYS_EXPECT_EQUAL("Mod Mat4x4", Mod(mat, modMat), result);
  }
}
