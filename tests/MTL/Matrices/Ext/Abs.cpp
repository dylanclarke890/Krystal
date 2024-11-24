#include "MTL/Matrices/Ext/Abs.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Abs()
  {
    // mat2x2
    constexpr mat2x2_t<int> v1 {-1, -2, -3, -4};
    KRYS_EXPECT_EQUAL("Abs Mat2x2", Abs(v1), (mat2x2_t<int> {1, 2, 3, 4}));

    // mat3x3
    constexpr mat3x3_t<int> v2 {-1, -2, -3, -4, -5, 6, -7, -8, -9};
    KRYS_EXPECT_EQUAL("Abs Mat3x3", Abs(v2), (mat3x3_t<int> {1, 2, 3, 4, 5, 6, 7, 8, 9}));

    // mat4x4
    constexpr mat4x4_t<int> v3 {-1, -2, -3, -4, -5, 6, -7, -8, -9, -10, 11, 12, -13, -14, -15, -16};
    KRYS_EXPECT_EQUAL("Abs Mat4x4", Abs(v3),
                      (mat4x4_t<int> {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
  }
}