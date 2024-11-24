#include "MTL/Matrices/Ext/Max.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Max()
  {
    // mat2x2
    constexpr mat2x2_t<int> v1 {1, -2, 3, -4};
    constexpr int scalar1 = 0;
    KRYS_EXPECT_EQUAL("Max Mat2x2", Max(v1, scalar1), (mat2x2_t<int> {1, 0, 3, 0}));

    // mat3x3
    constexpr mat3x3_t<int> v2 {1, -1, 0, 5, -5, 10, 4, 3, -3};
    constexpr int scalar2 = 5;
    KRYS_EXPECT_EQUAL("Max Mat3x3", Max(v2, scalar2), (mat3x3_t<int> {5, 5, 5, 5, 5, 10, 5, 5, 5}));

    // mat4x4
    constexpr mat4x4_t<int> v3 {10, 20, 30, 40, -5, -15, -25, -35, 0, 5, 15, 25, -10, -20, -30, -40};
    constexpr int scalar3 = 25;
    KRYS_EXPECT_EQUAL("Max Mat4x4", Max(v3, scalar3),
                      (mat4x4_t<int> {25, 25, 30, 40, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25}));
  }
}