#include "MTL/Matrices/Ext/Abs.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat2x3.hpp"
#include "MTL/Matrices/Mat2x4.hpp"
#include "MTL/Matrices/Mat3x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x2.hpp"
#include "MTL/Matrices/Mat4x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Mat2x2_Abs()
  {
    using mat_t = Mat2x2;
    constexpr mat_t mat {-1, -2, -3, -4};
    KRYS_EXPECT_EQUAL("Abs Mat2x2", Abs(mat), mat_t(1, 2, 3, 4));
  }

  static void Test_Mat2x3_Abs()
  {
    using mat_t = Mat2x3;
    constexpr mat_t mat {-1, -2, -3, -4, -5, -6};
    KRYS_EXPECT_EQUAL("Abs Mat2x3", Abs(mat), mat_t(1, 2, 3, 4, 5, 6));
  }

  static void Test_Mat2x4_Abs()
  {
    using mat_t = Mat2x4;
    constexpr mat_t mat {-1, -2, -3, -4, -5, -6, -7, -8};
    KRYS_EXPECT_EQUAL("Abs Mat2x4", Abs(mat), mat_t(1, 2, 3, 4, 5, 6, 7, 8));
  }

  static void Test_Mat3x2_Abs()
  {
    using mat_t = Mat3x2;
    constexpr mat_t mat {-1, -2, -3, -4, -5, -6};
    KRYS_EXPECT_EQUAL("Abs Mat3x2", Abs(mat), mat_t(1, 2, 3, 4, 5, 6));
  }

  static void Test_Mat3x3_Abs()
  {
    using mat_t = Mat3x3;
    constexpr mat_t mat {-1, -2, -3, -4, -5, -6, 7, -8, -9};
    KRYS_EXPECT_EQUAL("Abs Mat3x3", Abs(mat), mat_t(1, 2, 3, 4, 5, 6, 7, 8, 9));
  }

  static void Test_Mat3x4_Abs()
  {
    using mat_t = Mat3x4;
    constexpr mat_t mat {-1, -2, -3, -4, -5, -6, -7, -8, 9, -10, 11, 12};
    KRYS_EXPECT_EQUAL("Abs Mat3x4", Abs(mat), mat_t(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
  }

  static void Test_Mat4x2_Abs()
  {
    using mat_t = Mat4x2;
    constexpr mat_t mat {-1, -2, -3, -4, -5, -6, -7, -8};
    KRYS_EXPECT_EQUAL("Abs Mat4x2", Abs(mat), mat_t(1, 2, 3, 4, 5, 6, 7, 8));
  }

  static void Test_Mat4x3_Abs()
  {
    using mat_t = Mat4x3;
    constexpr mat_t mat {-1, -2, -3, -4, -5, -6, -7, -8, 9, -10, 11, 12};
    KRYS_EXPECT_EQUAL("Abs Mat4x3", Abs(mat), mat_t(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
  }

  static void Test_Mat4x4_Abs()
  {
    using mat_t = Mat4x4;
    constexpr mat_t mat {-1, -2, -3, -4, -5, -6, -7, -8, 9, -10, 11, 12, -13, -14, -15, -16};
    KRYS_EXPECT_EQUAL("Abs Mat4x4", Abs(mat), mat_t(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
  }
}