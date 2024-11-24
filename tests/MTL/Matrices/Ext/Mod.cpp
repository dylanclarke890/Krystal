#include "MTL/Matrices/Ext/Mod.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Mod()
  {
    // mat2x2
    constexpr mat2x2_t<int> v1 {10, -20, 30, -40};
    constexpr mat2x2_t<int> mod1 {7, 5, 6, 3};
    KRYS_EXPECT_EQUAL("Mod Mat2x2", Mod(v1, mod1), (mat2x2_t<int> {3, 0, 0, -1}));

    // mat3x3
    constexpr mat3x3_t<int> v2 {-10, -5, 0, 5, 10, 15, -3, 4, 6};
    constexpr mat3x3_t<int> mod2 {4, 3, 7, 6, 2, 10, 5, 3, 4};
    KRYS_EXPECT_EQUAL("Mod Mat3x3", Mod(v2, mod2), (mat3x3_t<int> {-2, -2, 0, 5, 0, 5, -3, 1, 2}));

    // mat4x4
    constexpr mat4x4_t<int> v3 {-20, -10, 0, 10, 20, 30, -15, 15, 25, 5, -5, 0, -1, 1, 50, -50};
    constexpr mat4x4_t<int> mod3 {8, 5, 10, 15, 20, 25, 30, 35, 40, 3, 4, 6, 7, 9, 12, 13};
    KRYS_EXPECT_EQUAL("Mod Mat4x4", Mod(v3, mod3),
                      (mat4x4_t<int> {-4, 0, 0, 10, 0, 5, -15, 15, 25, 2, -1, 0, -1, 1, 2, -11}));
  }
}
