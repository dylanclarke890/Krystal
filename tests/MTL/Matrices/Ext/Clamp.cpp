#include "MTL/Matrices/Ext/Clamp.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Clamp()
  {
    // mat2x2
    constexpr mat2x2_t<int> v1 {1, -2, 3, -4};
    constexpr int min1 = 0, max1 = 2;
    KRYS_EXPECT_EQUAL("Clamp Mat2x2", Clamp(v1, min1, max1), (mat2x2_t<int> {1, 0, 2, 0}));

    // mat3x3
    constexpr mat3x3_t<int> v2 {-10, -5, 0, 5, 10, 15, -3, 4, 6};
    constexpr int min2 = -5, max2 = 5;
    KRYS_EXPECT_EQUAL("Clamp Mat3x3", Clamp(v2, min2, max2), (mat3x3_t<int> {-5, -5, 0, 5, 5, 5, -3, 4, 5}));

    // mat4x4
    constexpr mat4x4_t<int> v3 {-20, -10, 0, 10, 20, 30, -15, 15, 25, 5, -5, 0, -1, 1, 50, -50};
    constexpr int min3 = -10, max3 = 10;
    KRYS_EXPECT_EQUAL("Clamp Mat4x4", Clamp(v3, min3, max3),
                      (mat4x4_t<int> {-10, -10, 0, 10, 10, 10, -10, 10, 10, 5, -5, 0, -1, 1, 10, -10}));
  }
}
