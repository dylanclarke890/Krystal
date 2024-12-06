#include "MTL/Matrices/Ext/Comparison.hpp"
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

  static void Test_Mat2x2_Comparison()
  {
    using res_t = mat2x2_t<bool>;
    constexpr Mat2x2 a {1, 2, 3, 4};
    constexpr Mat2x2 b {1, 2, 4, 3};

    KRYS_EXPECT_EQUAL("Comparison (LT) Mat2x2-Mat2x2", LessThan(a, b), res_t(false, false, true, false));
    KRYS_EXPECT_TRUE("Comparison (LT) Mat2x2-Scalar", LessThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (LE) Mat2x2-Mat2x2", LessThanOrEqual(a, b), res_t(true, true, true, false));
    KRYS_EXPECT_TRUE("Comparison (LE) Mat2x2-Scalar", LessThanOrEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (EQ) Mat2x2-Mat2x2", Equal(a, b), res_t(true, true, false, false));
    KRYS_EXPECT_FALSE("Comparison (EQ) Mat2x2-Scalar", Equal(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (NE) Mat2x2-Mat2x2", NotEqual(a, b), res_t(false, false, true, true));
    KRYS_EXPECT_TRUE("Comparison (NE) Mat2x2-Scalar", NotEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GT) Mat2x2-Mat2x2", GreaterThan(a, b), res_t(false, false, false, true));
    KRYS_EXPECT_FALSE("Comparison (GT) Mat2x2-Scalar", GreaterThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GE) Mat2x2-Mat2x2", GreaterThanOrEqual(a, b),
                      res_t(true, true, false, true));
    KRYS_EXPECT_FALSE("Comparison (GE) Mat2x2-Scalar", GreaterThanOrEqual(a, 5.0f));
  }

  static void Test_Mat2x3_Comparison()
  {
    using res_t = mat2x3_t<bool>;
    constexpr Mat2x3 a {1, 2, 3, 4, 3, 2};
    constexpr Mat2x3 b {1, 2, 4, 3, 2, 3};

    KRYS_EXPECT_EQUAL("Comparison (LT) Mat2x3-Mat2x3", LessThan(a, b),
                      res_t(false, false, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LT) Mat2x3-Scalar", LessThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (LE) Mat2x3-Mat2x3", LessThanOrEqual(a, b),
                      res_t(true, true, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LE) Mat2x3-Scalar", LessThanOrEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (EQ) Mat2x3-Mat2x3", Equal(a, b),
                      res_t(true, true, false, false, false, false));
    KRYS_EXPECT_FALSE("Comparison (EQ) Mat2x3-Scalar", Equal(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (NE) Mat2x3-Mat2x3", NotEqual(a, b),
                      res_t(false, false, true, true, true, true));
    KRYS_EXPECT_TRUE("Comparison (NE) Mat2x3-Scalar", NotEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GT) Mat2x3-Mat2x3", GreaterThan(a, b),
                      res_t(false, false, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GT) Mat2x3-Scalar", GreaterThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GE) Mat2x3-Mat2x3", GreaterThanOrEqual(a, b),
                      res_t(true, true, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GE) Mat2x3-Scalar", GreaterThanOrEqual(a, 5.0f));
  }

  static void Test_Mat2x4_Comparison()
  {
    using res_t = mat2x4_t<bool>;
    constexpr Mat2x4 a {1, 2, 3, 4, 3, 2};
    constexpr Mat2x4 b {1, 2, 4, 3, 2, 3};

    KRYS_EXPECT_EQUAL("Comparison (LT) Mat2x4-Mat2x4", LessThan(a, b),
                      res_t(false, false, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LT) Mat2x4-Scalar", LessThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (LE) Mat2x4-Mat2x4", LessThanOrEqual(a, b),
                      res_t(true, true, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LE) Mat2x4-Scalar", LessThanOrEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (EQ) Mat2x4-Mat2x4", Equal(a, b),
                      res_t(true, true, false, false, false, false));
    KRYS_EXPECT_FALSE("Comparison (EQ) Mat2x4-Scalar", Equal(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (NE) Mat2x4-Mat2x4", NotEqual(a, b),
                      res_t(false, false, true, true, true, true));
    KRYS_EXPECT_TRUE("Comparison (NE) Mat2x4-Scalar", NotEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GT) Mat2x4-Mat2x4", GreaterThan(a, b),
                      res_t(false, false, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GT) Mat2x4-Scalar", GreaterThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GE) Mat2x4-Mat2x4", GreaterThanOrEqual(a, b),
                      res_t(true, true, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GE) Mat2x4-Scalar", GreaterThanOrEqual(a, 5.0f));
  }

  static void Test_Mat3x2_Comparison()
  {
    using res_t = mat3x2_t<bool>;
    constexpr Mat3x2 a {1, 2, 3, 4, 3, 2};
    constexpr Mat3x2 b {1, 2, 4, 3, 2, 3};

    KRYS_EXPECT_EQUAL("Comparison (LT) Mat3x2-Mat3x2", LessThan(a, b),
                      res_t(false, false, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LT) Mat3x2-Scalar", LessThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (LE) Mat3x2-Mat3x2", LessThanOrEqual(a, b),
                      res_t(true, true, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LE) Mat3x2-Scalar", LessThanOrEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (EQ) Mat3x2-Mat3x2", Equal(a, b),
                      res_t(true, true, false, false, false, false));
    KRYS_EXPECT_FALSE("Comparison (EQ) Mat3x2-Scalar", Equal(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (NE) Mat3x2-Mat3x2", NotEqual(a, b),
                      res_t(false, false, true, true, true, true));
    KRYS_EXPECT_TRUE("Comparison (NE) Mat3x2-Scalar", NotEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GT) Mat3x2-Mat3x2", GreaterThan(a, b),
                      res_t(false, false, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GT) Mat3x2-Scalar", GreaterThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GE) Mat3x2-Mat3x2", GreaterThanOrEqual(a, b),
                      res_t(true, true, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GE) Mat3x2-Scalar", GreaterThanOrEqual(a, 5.0f));
  }

  static void Test_Mat3x3_Comparison()
  {
    using res_t = mat3x3_t<bool>;
    constexpr Mat3x3 a {1, 2, 3, 4, 3, 2};
    constexpr Mat3x3 b {1, 2, 4, 3, 2, 3};

    KRYS_EXPECT_EQUAL("Comparison (LT) Mat3x3-Mat3x3", LessThan(a, b),
                      res_t(false, false, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LT) Mat3x3-Scalar", LessThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (LE) Mat3x3-Mat3x3", LessThanOrEqual(a, b),
                      res_t(true, true, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LE) Mat3x3-Scalar", LessThanOrEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (EQ) Mat3x3-Mat3x3", Equal(a, b),
                      res_t(true, true, false, false, false, false));
    KRYS_EXPECT_FALSE("Comparison (EQ) Mat3x3-Scalar", Equal(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (NE) Mat3x3-Mat3x3", NotEqual(a, b),
                      res_t(false, false, true, true, true, true));
    KRYS_EXPECT_TRUE("Comparison (NE) Mat3x3-Scalar", NotEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GT) Mat3x3-Mat3x3", GreaterThan(a, b),
                      res_t(false, false, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GT) Mat3x3-Scalar", GreaterThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GE) Mat3x3-Mat3x3", GreaterThanOrEqual(a, b),
                      res_t(true, true, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GE) Mat3x3-Scalar", GreaterThanOrEqual(a, 5.0f));
  }

  static void Test_Mat3x4_Comparison()
  {
    using res_t = mat3x4_t<bool>;
    constexpr Mat3x4 a {1, 2, 3, 4, 3, 2};
    constexpr Mat3x4 b {1, 2, 4, 3, 2, 3};

    KRYS_EXPECT_EQUAL("Comparison (LT) Mat3x4-Mat3x4", LessThan(a, b),
                      res_t(false, false, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LT) Mat3x4-Scalar", LessThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (LE) Mat3x4-Mat3x4", LessThanOrEqual(a, b),
                      res_t(true, true, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LE) Mat3x4-Scalar", LessThanOrEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (EQ) Mat3x4-Mat3x4", Equal(a, b),
                      res_t(true, true, false, false, false, false));
    KRYS_EXPECT_FALSE("Comparison (EQ) Mat3x4-Scalar", Equal(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (NE) Mat3x4-Mat3x4", NotEqual(a, b),
                      res_t(false, false, true, true, true, true));
    KRYS_EXPECT_TRUE("Comparison (NE) Mat3x4-Scalar", NotEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GT) Mat3x4-Mat3x4", GreaterThan(a, b),
                      res_t(false, false, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GT) Mat3x4-Scalar", GreaterThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GE) Mat3x4-Mat3x4", GreaterThanOrEqual(a, b),
                      res_t(true, true, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GE) Mat3x4-Scalar", GreaterThanOrEqual(a, 5.0f));
  }

  static void Test_Mat4x2_Comparison()
  {
    using res_t = mat4x2_t<bool>;
    constexpr Mat4x2 a {1, 2, 3, 4, 3, 2};
    constexpr Mat4x2 b {1, 2, 4, 3, 2, 3};

    KRYS_EXPECT_EQUAL("Comparison (LT) Mat4x2-Mat4x2", LessThan(a, b),
                      res_t(false, false, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LT) Mat4x2-Scalar", LessThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (LE) Mat4x2-Mat4x2", LessThanOrEqual(a, b),
                      res_t(true, true, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LE) Mat4x2-Scalar", LessThanOrEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (EQ) Mat4x2-Mat4x2", Equal(a, b),
                      res_t(true, true, false, false, false, false));
    KRYS_EXPECT_FALSE("Comparison (EQ) Mat4x2-Scalar", Equal(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (NE) Mat4x2-Mat4x2", NotEqual(a, b),
                      res_t(false, false, true, true, true, true));
    KRYS_EXPECT_TRUE("Comparison (NE) Mat4x2-Scalar", NotEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GT) Mat4x2-Mat4x2", GreaterThan(a, b),
                      res_t(false, false, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GT) Mat4x2-Scalar", GreaterThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GE) Mat4x2-Mat4x2", GreaterThanOrEqual(a, b),
                      res_t(true, true, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GE) Mat4x2-Scalar", GreaterThanOrEqual(a, 5.0f));
  }

  static void Test_Mat4x3_Comparison()
  {
    using res_t = mat2x4_t<bool>;
    constexpr Mat2x4 a {1, 2, 3, 4, 3, 2};
    constexpr Mat2x4 b {1, 2, 4, 3, 2, 3};

    KRYS_EXPECT_EQUAL("Comparison (LT) Mat2x4-Mat2x4", LessThan(a, b),
                      res_t(false, false, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LT) Mat2x4-Scalar", LessThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (LE) Mat2x4-Mat2x4", LessThanOrEqual(a, b),
                      res_t(true, true, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LE) Mat2x4-Scalar", LessThanOrEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (EQ) Mat2x4-Mat2x4", Equal(a, b),
                      res_t(true, true, false, false, false, false));
    KRYS_EXPECT_FALSE("Comparison (EQ) Mat2x4-Scalar", Equal(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (NE) Mat2x4-Mat2x4", NotEqual(a, b),
                      res_t(false, false, true, true, true, true));
    KRYS_EXPECT_TRUE("Comparison (NE) Mat2x4-Scalar", NotEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GT) Mat2x4-Mat2x4", GreaterThan(a, b),
                      res_t(false, false, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GT) Mat2x4-Scalar", GreaterThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GE) Mat2x4-Mat2x4", GreaterThanOrEqual(a, b),
                      res_t(true, true, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GE) Mat2x4-Scalar", GreaterThanOrEqual(a, 5.0f));
  }

  static void Test_Mat4x4_Comparison()
  {
    using res_t = mat4x4_t<bool>;
    constexpr Mat4x4 a {1, 2, 3, 4, 3, 2};
    constexpr Mat4x4 b {1, 2, 4, 3, 2, 3};

    KRYS_EXPECT_EQUAL("Comparison (LT) Mat4x4-Mat4x4", LessThan(a, b),
                      res_t(false, false, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LT) Mat4x4-Scalar", LessThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (LE) Mat4x4-Mat4x4", LessThanOrEqual(a, b),
                      res_t(true, true, true, false, false, true));
    KRYS_EXPECT_TRUE("Comparison (LE) Mat4x4-Scalar", LessThanOrEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (EQ) Mat4x4-Mat4x4", Equal(a, b),
                      res_t(true, true, false, false, false, false));
    KRYS_EXPECT_FALSE("Comparison (EQ) Mat4x4-Scalar", Equal(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (NE) Mat4x4-Mat4x4", NotEqual(a, b),
                      res_t(false, false, true, true, true, true));
    KRYS_EXPECT_TRUE("Comparison (NE) Mat4x4-Scalar", NotEqual(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GT) Mat4x4-Mat4x4", GreaterThan(a, b),
                      res_t(false, false, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GT) Mat4x4-Scalar", GreaterThan(a, 5.0f));

    KRYS_EXPECT_EQUAL("Comparison (GE) Mat4x4-Mat4x4", GreaterThanOrEqual(a, b),
                      res_t(true, true, false, true, true, false));
    KRYS_EXPECT_FALSE("Comparison (GE) Mat4x4-Scalar", GreaterThanOrEqual(a, 5.0f));
  }
}
