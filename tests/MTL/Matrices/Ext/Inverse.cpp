#include "MTL/Matrices/Ext/Inverse.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Inverse()
  {
    constexpr matrix_t<float, 2, 2> m2x2 {vec2_t<float> {4, 2}, vec2_t<float> {7, 6}};
    KRYS_EXPECT_EQUAL("Inverse Mat2x2", Inverse(m2x2),
                      (mat2x2_t<float> {vec2_t<float> {0.6f, -0.2f}, vec2_t<float> {-0.7f, 0.4f}}));

    constexpr matrix_t<float, 3, 3> m3x3 {vec3_t<float> {1, -1, 1}, vec3_t<float> {2, 0, -1},
                                          vec3_t<float> {-1, 1, 0}};
    KRYS_EXPECT_EQUAL("Inverse Mat2x2", Inverse(m2x2),
                      (mat2x2_t<float> {vec2_t<float> {0.6f, -0.2f}, vec2_t<float> {-0.7f, 0.4f}}));

    constexpr matrix_t<float, 4, 4> m4x4 {vec4_t<float> {1, 2, 3, 4}, vec4_t<float> {5, 6, 7, 8},
                                          vec4_t<float> {9, 10, 11, 12}, vec4_t<float> {13, 14, 15, 16}};
  }
}