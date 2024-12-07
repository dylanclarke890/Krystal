#include "MTL/Matrices/Ext/Transpose.hpp"
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

  static void Test_Mat2x2_Transpose()
  {
    constexpr Mat2x2 mat {{1, 2}, {3, 4}};
    KRYS_EXPECT_EQUAL("Transpose Mat2x2", Transpose(Transpose(mat)), mat);
  }

  static void Test_Mat2x3_Transpose()
  {
    constexpr Mat2x3 mat {{1, 2}, {3, 4}, {5, 6}};
    KRYS_EXPECT_EQUAL("Transpose Mat2x3", Transpose(Transpose(mat)), mat);
  }

  static void Test_Mat2x4_Transpose()
  {
    constexpr Mat2x4 mat {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    KRYS_EXPECT_EQUAL("Transpose Mat2x4", Transpose(Transpose(mat)), mat);
  }

  static void Test_Mat3x2_Transpose()
  {
    constexpr Mat3x2 mat {{1, 2, 3}, {4, 5, 6}};
    KRYS_EXPECT_EQUAL("Transpose Mat3x2", Transpose(Transpose(mat)), mat);
  }

  static void Test_Mat3x3_Transpose()
  {
    constexpr Mat3x3 mat {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    KRYS_EXPECT_EQUAL("Transpose Mat3x3", Transpose(Transpose(mat)), mat);
  }

  static void Test_Mat3x4_Transpose()
  {
    constexpr Mat3x4 mat {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    KRYS_EXPECT_EQUAL("Transpose Mat3x4", Transpose(Transpose(mat)), mat);
  }

  static void Test_Mat4x2_Transpose()
  {
    constexpr Mat4x2 mat {{1, 2, 3, 4}, {5, 6, 7, 8}};
    KRYS_EXPECT_EQUAL("Transpose Mat4x2", Transpose(Transpose(mat)), mat);
  }

  static void Test_Mat4x3_Transpose()
  {
    constexpr Mat4x3 mat {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    KRYS_EXPECT_EQUAL("Transpose Mat4x3", Transpose(Transpose(mat)), mat);
  }

  static void Test_Mat4x4_Transpose()
  {
    constexpr Mat4x4 mat {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    KRYS_EXPECT_EQUAL("Transpose Mat4x4", Transpose(Transpose(mat)), mat);
  }
}