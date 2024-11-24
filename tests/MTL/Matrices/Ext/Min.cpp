#include "MTL/Matrices/Ext/Min.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Min()
  {
    // mat2x2
    constexpr mat2x2_t<int> v1 {1, -2, 3, -4};
    constexpr int scalar1 = 1;
    KRYS_EXPECT_EQUAL("Min Mat2x2", Min(v1, scalar1), (mat2x2_t<int> {1, -2, 1, -4}));

    // mat3x3
    constexpr mat3x3_t<int> v2 {1, -1, 0, 5, -5, 10, 4, 3, -3};
    constexpr int scalar2 = -3;
    KRYS_EXPECT_EQUAL("Min Mat3x3", Min(v2, scalar2), (mat3x3_t<int> {-3, -3, -3, -3, -5, -3, -3, -3, -3}));

    // mat4x4
    constexpr mat4x4_t<int> v3 {10, 20, 30, 40, -5, -15, -25, -35, 0, 5, 15, 25, -10, -20, -30, -40};
    constexpr int scalar3 = -10;
    KRYS_EXPECT_EQUAL(
      "Min Mat4x4", Min(v3, scalar3),
      (mat4x4_t<int> {-10, -10, -10, -10, -10, -15, -25, -35, -10, -10, -10, -10, -10, -20, -30, -40}));
  }
}
