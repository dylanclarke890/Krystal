#include "MTL/Matrices/Ext/Determinant.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Mat2x2_Determinant()
  {
    constexpr mat2x2_t<int> mat {{4, 3}, {6, 8}};
    KRYS_EXPECT_EQUAL("Determinant Mat2x2", Determinant(mat), 14);
  }

  static void Test_Mat3x3_Determinant()
  {
    constexpr mat3x3_t<int> mat {{6, 4, 2}, {1, -2, 8}, {1, 5, 7}};
    KRYS_EXPECT_EQUAL("Determinant Mat3x3", Determinant(mat), -306);
  }

  static void Test_Mat4x4_Determinant()
  {
    constexpr mat4x4_t<int> mat {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    KRYS_EXPECT_EQUAL("Determinant Mat4x4", Determinant(mat), 0);

    constexpr mat4x4_t<int> nonSingular {4, 2, 3, 1, 6, 8, 7, 5, 1, -2, 8, 3, 5, 1, 4, 7};
    KRYS_EXPECT_EQUAL("Determinant Non-Singular Mat4x4", Determinant(nonSingular), 1'066);
  }
}