#include "MTL/Matrices/Ext/Rounding.hpp"
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

  static void Test_Rounding_Mat2x2()
  {
    using mat_t = Mat2x2;
    constexpr mat_t mat {1.1f, 2.6f, 3.5f, 5.0f};

    KRYS_EXPECT_EQUAL("Ceil Mat2x2", Ceil(mat), mat_t(2, 3, 4, 5));
    KRYS_EXPECT_EQUAL("Floor Mat2x2", Floor(mat), mat_t(1, 2, 3, 5));
    KRYS_EXPECT_EQUAL("Round Mat2x2", Round(mat), mat_t(1, 3, 4, 5));
    KRYS_EXPECT_EQUAL("Trunc Mat2x2", Trunc(mat), mat_t(1, 2, 3, 5));
  }

  static void Test_Rounding_Mat2x3()
  {
    using mat_t = Mat2x3;
    constexpr mat_t mat {1.1f, 2.6f, 3.5f, 5.0f, -1.1f, -2.0f};

    KRYS_EXPECT_EQUAL("Ceil Mat2x3", Ceil(mat), mat_t(2, 3, 4, 5, -1, -2));
    KRYS_EXPECT_EQUAL("Floor Mat2x3", Floor(mat), mat_t(1, 2, 3, 5, -2, -2));
    KRYS_EXPECT_EQUAL("Round Mat2x3", Round(mat), mat_t(1, 3, 4, 5, -1, -2));
    KRYS_EXPECT_EQUAL("Trunc Mat2x3", Trunc(mat), mat_t(1, 2, 3, 5, -1, -2));
  }

  static void Test_Rounding_Mat2x4()
  {
    using mat_t = Mat2x4;
    constexpr mat_t mat {1.1f, 2.6f, 3.5f, 5.0f, -1.1f, -2.0f, -3.5f, -4.0f};

    KRYS_EXPECT_EQUAL("Ceil Mat2x4", Ceil(mat), mat_t(2, 3, 4, 5, -1, -2, -3, -4));
    KRYS_EXPECT_EQUAL("Floor Mat2x4", Floor(mat), mat_t(1, 2, 3, 5, -2, -2, -4, -4));
    KRYS_EXPECT_EQUAL("Round Mat2x4", Round(mat), mat_t(1, 3, 4, 5, -1, -2, -4, -4));
    KRYS_EXPECT_EQUAL("Trunc Mat2x4", Trunc(mat), mat_t(1, 2, 3, 5, -1, -2, -3, -4));
  }

  static void Test_Rounding_Mat3x2()
  {
    using mat_t = Mat3x2;
    constexpr mat_t mat {1.1f, 2.6f, 3.5f, 5.0f, -1.1f, -2.0f};

    KRYS_EXPECT_EQUAL("Ceil Mat3x2", Ceil(mat), mat_t(2, 3, 4, 5, -1, -2));
    KRYS_EXPECT_EQUAL("Floor Mat3x2", Floor(mat), mat_t(1, 2, 3, 5, -2, -2));
    KRYS_EXPECT_EQUAL("Round Mat3x2", Round(mat), mat_t(1, 3, 4, 5, -1, -2));
    KRYS_EXPECT_EQUAL("Trunc Mat3x2", Trunc(mat), mat_t(1, 2, 3, 5, -1, -2));
  }

  static void Test_Rounding_Mat3x3()
  {
    using mat_t = Mat3x3;
    constexpr mat_t mat {1.1f, 2.6f, 3.5f, 5.0f, -1.1f, -2.0f, 3.5f, 4.0f, 2.1f};

    KRYS_EXPECT_EQUAL("Ceil Mat3x3", Ceil(mat), mat_t(2, 3, 4, 5, -1, -2, 4, 4, 3));
    KRYS_EXPECT_EQUAL("Floor Mat3x3", Floor(mat), mat_t(1, 2, 3, 5, -2, -2, 3, 4, 2));
    KRYS_EXPECT_EQUAL("Round Mat3x3", Round(mat), mat_t(1, 3, 4, 5, -1, -2, 4, 4, 2));
    KRYS_EXPECT_EQUAL("Trunc Mat3x3", Trunc(mat), mat_t(1, 2, 3, 5, -1, -2, 3, 4, 2));
  }

  static void Test_Rounding_Mat3x4()
  {
    using mat_t = Mat3x4;
    constexpr mat_t mat {1.1f, 2.6f, 3.5f, 5.0f, -1.1f, -2.0f, 3.5f, 4.0f, 2.1f, 2.5f, 3.5f, 5.6f};

    KRYS_EXPECT_EQUAL("Ceil Mat3x4", Ceil(mat), mat_t(2, 3, 4, 5, -1, -2, 4, 4, 3, 3, 4, 6));
    KRYS_EXPECT_EQUAL("Floor Mat3x4", Floor(mat), mat_t(1, 2, 3, 5, -2, -2, 3, 4, 2, 2, 3, 5));
    KRYS_EXPECT_EQUAL("Round Mat3x4", Round(mat), mat_t(1, 3, 4, 5, -1, -2, 4, 4, 2, 3, 4, 6));
    KRYS_EXPECT_EQUAL("Trunc Mat3x4", Trunc(mat), mat_t(1, 2, 3, 5, -1, -2, 3, 4, 2, 2, 3, 5));
  }

  static void Test_Rounding_Mat4x2()
  {
    using mat_t = Mat4x2;
    constexpr mat_t mat {1.1f, 2.6f, 3.5f, 5.0f, -1.1f, -2.0f, -3.5f, -4.0f};

    KRYS_EXPECT_EQUAL("Ceil Mat4x2", Ceil(mat), mat_t(2, 3, 4, 5, -1, -2, -3, -4));
    KRYS_EXPECT_EQUAL("Floor Mat4x2", Floor(mat), mat_t(1, 2, 3, 5, -2, -2, -4, -4));
    KRYS_EXPECT_EQUAL("Round Mat4x2", Round(mat), mat_t(1, 3, 4, 5, -1, -2, -4, -4));
    KRYS_EXPECT_EQUAL("Trunc Mat4x2", Trunc(mat), mat_t(1, 2, 3, 5, -1, -2, -3, -4));
  }

  static void Test_Rounding_Mat4x3()
  {
    using mat_t = Mat4x3;
    constexpr mat_t mat {1.1f, 2.6f, 3.5f, 5.0f, -1.1f, -2.0f, 3.5f, 4.0f, 2.1f, 2.5f, 3.5f, 5.6f};

    KRYS_EXPECT_EQUAL("Ceil Mat4x3", Ceil(mat), mat_t(2, 3, 4, 5, -1, -2, 4, 4, 3, 3, 4, 6));
    KRYS_EXPECT_EQUAL("Floor Mat4x3", Floor(mat), mat_t(1, 2, 3, 5, -2, -2, 3, 4, 2, 2, 3, 5));
    KRYS_EXPECT_EQUAL("Round Mat4x3", Round(mat), mat_t(1, 3, 4, 5, -1, -2, 4, 4, 2, 3, 4, 6));
    KRYS_EXPECT_EQUAL("Trunc Mat4x3", Trunc(mat), mat_t(1, 2, 3, 5, -1, -2, 3, 4, 2, 2, 3, 5));
  }

  static void Test_Rounding_Mat4x4()
  {
    using mat_t = Mat4x4;
    constexpr mat_t mat {1.1f, 2.6f, 3.5f, 5.0f, -1.1f, -2.0f, 3.5f,  4.0f,
                         2.1f, 2.5f, 3.5f, 5.6f, 9.9f,  10.0f, 10.1f, 0.0f};

    KRYS_EXPECT_EQUAL("Ceil Mat4x4", Ceil(mat), mat_t(2, 3, 4, 5, -1, -2, 4, 4, 3, 3, 4, 6, 10, 10, 11, 0));
    KRYS_EXPECT_EQUAL("Floor Mat4x4", Floor(mat), mat_t(1, 2, 3, 5, -2, -2, 3, 4, 2, 2, 3, 5, 9, 10, 10, 0));
    KRYS_EXPECT_EQUAL("Round Mat4x4", Round(mat), mat_t(1, 3, 4, 5, -1, -2, 4, 4, 2, 3, 4, 6, 10, 10, 10, 0));
    KRYS_EXPECT_EQUAL("Trunc Mat4x4", Trunc(mat), mat_t(1, 2, 3, 5, -1, -2, 3, 4, 2, 2, 3, 5, 9, 10, 10, 0));
  }
}
