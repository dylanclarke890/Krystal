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

  static void Test_Transpose()
  {
    constexpr Mat2x2 mat2x2 {{1, 2}, {3, 4}};
    KRYS_EXPECT_EQUAL("Transpose Mat2x2", Transpose(Transpose(mat2x2)), mat2x2);

    constexpr Mat2x3 mat2x3 {{1, 2}, {3, 4}, {5, 6}};
    KRYS_EXPECT_EQUAL("Transpose Mat2x3", Transpose(Transpose(mat2x3)), mat2x3);

    constexpr Mat2x4 mat2x4 {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    KRYS_EXPECT_EQUAL("Transpose Mat2x4", Transpose(Transpose(mat2x4)), mat2x4);

    constexpr Mat3x2 mat3x2 {{1, 2, 3}, {4, 5, 6}};
    KRYS_EXPECT_EQUAL("Transpose Mat3x2", Transpose(Transpose(mat3x2)), mat3x2);

    constexpr Mat3x3 mat3x3 {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    KRYS_EXPECT_EQUAL("Transpose Mat3x3", Transpose(Transpose(mat3x3)), mat3x3);

    constexpr Mat3x4 mat3x4 {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    KRYS_EXPECT_EQUAL("Transpose Mat3x4", Transpose(Transpose(mat3x4)), mat3x4);

    constexpr Mat4x2 mat4x2 {{1, 2, 3, 4}, {5, 6, 7, 8}};
    KRYS_EXPECT_EQUAL("Transpose Mat4x2", Transpose(Transpose(mat4x2)), mat4x2);

    constexpr Mat4x3 mat4x3 {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    KRYS_EXPECT_EQUAL("Transpose Mat4x3", Transpose(Transpose(mat4x3)), mat4x3);

    constexpr Mat4x4 mat4x4 {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    KRYS_EXPECT_EQUAL("Transpose Mat4x4", Transpose(Transpose(mat4x4)), mat4x4);
  }
}