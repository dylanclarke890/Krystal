#include "MTL/Matrices/Ext/Predicate.hpp"
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

#pragma region Test Helpers

  constexpr auto IsMoreThan16 = [](int value)
  {
    return value > 16;
  };

  constexpr auto IsLessThan16 = [](int value)
  {
    return value < 16;
  };

#pragma endregion Test Helpers

  static void Test_Mat2x2_Predicate()
  {
    constexpr Mat2x2 mat {1, -1, 0, 5};
    KRYS_EXPECT_TRUE("AnyOf Mat2x2 (True)", AnyOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Mat2x2 (False)", AnyOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Mat2x2 (True)", AllOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Mat2x2 (False)", AllOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Mat2x2 (True)", NoneOf(mat, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Mat2x2 (False)", NoneOf(mat, IsLessThan16));
  }

  static void Test_Mat2x3_Predicate()
  {
    constexpr Mat2x3 mat {1, -1, 0, 5, 4, 2};
    KRYS_EXPECT_TRUE("AnyOf Mat2x3 (True)", AnyOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Mat2x3 (False)", AnyOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Mat2x3 (True)", AllOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Mat2x3 (False)", AllOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Mat2x3 (True)", NoneOf(mat, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Mat2x3 (False)", NoneOf(mat, IsLessThan16));
  }

  static void Test_Mat2x4_Predicate()
  {
    constexpr Mat2x4 mat {1, -1, 0, 5, 4, 2, 4, 1};
    KRYS_EXPECT_TRUE("AnyOf Mat2x4 (True)", AnyOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Mat2x4 (False)", AnyOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Mat2x4 (True)", AllOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Mat2x4 (False)", AllOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Mat2x4 (True)", NoneOf(mat, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Mat2x4 (False)", NoneOf(mat, IsLessThan16));
  }

  static void Test_Mat3x2_Predicate()
  {
    constexpr Mat3x2 mat {1, -1, 0, 5, 4, 2};
    KRYS_EXPECT_TRUE("AnyOf Mat3x2 (True)", AnyOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Mat3x2 (False)", AnyOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Mat3x2 (True)", AllOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Mat3x2 (False)", AllOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Mat3x2 (True)", NoneOf(mat, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Mat3x2 (False)", NoneOf(mat, IsLessThan16));
  }

  static void Test_Mat3x3_Predicate()
  {
    constexpr Mat3x3 mat {1, -1, 0, 5, 4, 2, 2, 1, 0};
    KRYS_EXPECT_TRUE("AnyOf Mat3x3 (True)", AnyOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Mat3x3 (False)", AnyOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Mat3x3 (True)", AllOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Mat3x3 (False)", AllOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Mat3x3 (True)", NoneOf(mat, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Mat3x3 (False)", NoneOf(mat, IsLessThan16));
  }

  static void Test_Mat3x4_Predicate()
  {
    constexpr Mat3x4 mat {1, -1, 0, 5, 4, 2, 2, 1, 0, 1, 3, 9};
    KRYS_EXPECT_TRUE("AnyOf Mat3x4 (True)", AnyOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Mat3x4 (False)", AnyOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Mat3x4 (True)", AllOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Mat3x4 (False)", AllOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Mat3x4 (True)", NoneOf(mat, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Mat3x4 (False)", NoneOf(mat, IsLessThan16));
  }

  static void Test_Mat4x2_Predicate()
  {
    constexpr Mat4x2 mat {1, -1, 0, 5, 4, 2, 4, 1};
    KRYS_EXPECT_TRUE("AnyOf Mat4x2 (True)", AnyOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Mat4x2 (False)", AnyOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Mat4x2 (True)", AllOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Mat4x2 (False)", AllOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Mat4x2 (True)", NoneOf(mat, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Mat4x2 (False)", NoneOf(mat, IsLessThan16));
  }

  static void Test_Mat4x3_Predicate()
  {
    constexpr Mat4x3 mat {1, -1, 0, 5, 4, 2, 2, 1, 0, 1, 3, 9};
    KRYS_EXPECT_TRUE("AnyOf Mat4x3 (True)", AnyOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Mat4x3 (False)", AnyOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Mat4x3 (True)", AllOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Mat4x3 (False)", AllOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Mat4x3 (True)", NoneOf(mat, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Mat4x3 (False)", NoneOf(mat, IsLessThan16));
  }

  static void Test_Mat4x4_Predicate()
  {
    constexpr Mat4x4 mat {1, -1, 0, 5, 4, 2, 2, 1, 0, 1, 3, 9, 11, 12, 13, 14};
    KRYS_EXPECT_TRUE("AnyOf Mat4x4 (True)", AnyOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Mat4x4 (False)", AnyOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Mat4x4 (True)", AllOf(mat, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Mat4x4 (False)", AllOf(mat, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Mat4x4 (True)", NoneOf(mat, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Mat4x4 (False)", NoneOf(mat, IsLessThan16));
  }
}
