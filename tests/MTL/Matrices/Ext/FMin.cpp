#include "MTL/Matrices/Ext/FMin.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_FMin()
  {
    // mat2x2
    constexpr mat2x2_t<float> v1 {1.0f, -2.0f, 3.0f, -4.0f};
    constexpr mat2x2_t<float> v2 {0.0f, 0.0f, 2.0f, 2.0f};
    KRYS_EXPECT_EQUAL("FMin Mat2x2", FMin(v1, v2), (mat2x2_t<float> {0.0f, -2.0f, 2.0f, -4.0f}));

    // mat3x3
    constexpr mat3x3_t<float> v3 {1.0f, -1.0f, 0.0f, 5.0f, -5.0f, 10.0f, 4.0f, 3.0f, -3.0f};
    constexpr mat3x3_t<float> v4 {2.0f, -2.0f, 1.0f, 0.0f, -10.0f, 5.0f, 5.0f, 0.0f, -1.0f};
    KRYS_EXPECT_EQUAL("FMin Mat3x3", FMin(v3, v4),
                      (mat3x3_t<float> {1.0f, -2.0f, 0.0f, 0.0f, -10.0f, 5.0f, 4.0f, 0.0f, -3.0f}));

    // mat4x4
    constexpr mat4x4_t<float> v5 {10.0f, 20.0f, 30.0f, 40.0f, -5.0f,  -15.0f, -25.0f, -35.0f,
                                  0.0f,  5.0f,  15.0f, 25.0f, -10.0f, -20.0f, -30.0f, -40.0f};
    constexpr mat4x4_t<float> v6 {15.0f, 10.0f, 35.0f, 20.0f, -10.0f, -10.0f, -30.0f, -40.0f,
                                  10.0f, 0.0f,  20.0f, 15.0f, -5.0f,  -15.0f, -35.0f, -45.0f};
    KRYS_EXPECT_EQUAL("FMin Mat4x4", FMin(v5, v6),
                      (mat4x4_t<float> {10.0f, 10.0f, 30.0f, 20.0f, -10.0f, -15.0f, -30.0f, -40.0f, 0.0f,
                                        0.0f, 15.0f, 15.0f, -10.0f, -20.0f, -35.0f, -45.0f}));
  }
}
