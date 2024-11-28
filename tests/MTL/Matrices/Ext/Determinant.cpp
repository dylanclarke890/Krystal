#include "MTL/Matrices/Ext/Determinant.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Determinant()
  {
    constexpr matrix_t<int, 2, 2> m2x2 {vec2_t<int> {4, 3}, vec2_t<int> {6, 8}};
    KRYS_EXPECT_EQUAL("Determinant Mat2x2", Determinant(m2x2), 14);

    constexpr matrix_t<int, 3, 3> m3x3 {vec3_t<int> {6, 4, 2}, vec3_t<int> {1, -2, 8}, vec3_t<int> {1, 5, 7}};
    KRYS_EXPECT_EQUAL("Determinant Mat3x3", Determinant(m3x3), -306);

    constexpr matrix_t<int, 4, 4> m4x4 {vec4_t<int> {1, 2, 3, 4}, vec4_t<int> {5, 6, 7, 8},
                                        vec4_t<int> {9, 10, 11, 12}, vec4_t<int> {13, 14, 15, 16}};
    KRYS_EXPECT_EQUAL("Determinant Mat4x4", Determinant(m4x4), 0);

    constexpr matrix_t<int, 4, 4> m4x4_non_singular {vec4_t<int> {4, 2, 3, 1}, vec4_t<int> {6, 8, 7, 5},
                                                     vec4_t<int> {1, -2, 8, 3}, vec4_t<int> {5, 1, 4, 7}};
    KRYS_EXPECT_EQUAL("Determinant Non-Singular Mat4x4", Determinant(m4x4_non_singular), 1'066);
  }
}