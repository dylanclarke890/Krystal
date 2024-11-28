#include "MTL/Matrices/Ext/Transpose.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Transpose()
  {
    constexpr mat2x2_t<int> m2x2 {vec2_t<int> {1, 2}, vec2_t<int> {3, 4}};
    KRYS_EXPECT_EQUAL("Transpose Mat2x2", Transpose(m2x2),
                      (mat2x2_t<int> {vec2_t<int> {1, 3}, vec2_t<int> {2, 4}}));

    constexpr mat3x3_t<int> m3x3 {vec3_t<int> {1, 2, 3}, vec3_t<int> {4, 5, 6}, vec3_t<int> {7, 8, 9}};
    KRYS_EXPECT_EQUAL("Transpose Mat3x3", Transpose(m3x3),
                      (mat3x3_t<int> {vec3_t<int> {1, 4, 7}, vec3_t<int> {2, 5, 8}, vec3_t<int> {3, 6, 9}}));

    constexpr mat4x4_t<int> m4x4 {vec4_t<int> {1, 2, 3, 4}, vec4_t<int> {5, 6, 7, 8},
                                  vec4_t<int> {9, 10, 11, 12}, vec4_t<int> {13, 14, 15, 16}};
    KRYS_EXPECT_EQUAL("Transpose Mat4x4", Transpose(m4x4),
                      (mat4x4_t<int> {vec4_t<int> {1, 5, 9, 13}, vec4_t<int> {2, 6, 10, 14},
                                      vec4_t<int> {3, 7, 11, 15}, vec4_t<int> {4, 8, 12, 16}}));
  }
}