#include "MTL/Matrices/Ext/Comparison.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Comparison()
  {
    // Mat2x2
    constexpr mat2x2_t<int> a2 {1, 2, 3, 4};
    constexpr mat2x2_t<int> b2 {2, 1, 3, 5};

    constexpr mat2x2_t<bool> expected_lt2 {true, false, false, true};
    constexpr mat2x2_t<bool> expected_le2 {true, false, true, true};
    constexpr mat2x2_t<bool> expected_eq2 {false, false, true, false};
    constexpr mat2x2_t<bool> expected_ne2 {true, true, false, true};
    constexpr mat2x2_t<bool> expected_gt2 {false, true, false, false};
    constexpr mat2x2_t<bool> expected_ge2 {false, true, true, false};

    KRYS_EXPECT_EQUAL("LessThan Mat2x2", LessThan(a2, b2), expected_lt2);
    KRYS_EXPECT_TRUE("LessThan Mat2x2 - Scalar", LessThan(a2, 5));
    KRYS_EXPECT_EQUAL("LessThanOrEqual Mat2x2", LessThanOrEqual(a2, b2), expected_le2);
    KRYS_EXPECT_TRUE("LessThanOrEqual Mat2x2 - Scalar", LessThanOrEqual(a2, 4));
    KRYS_EXPECT_EQUAL("Equal Mat2x2", Equal(a2, b2), expected_eq2);
    KRYS_EXPECT_FALSE("Equal Mat2x2 - Scalar", Equal(a2, 3));
    KRYS_EXPECT_EQUAL("NotEqual Mat2x2", NotEqual(a2, b2), expected_ne2);
    KRYS_EXPECT_TRUE("NotEqual Mat2x2 - Scalar", NotEqual(a2, 2));

    // Mat3x3
    constexpr mat3x3_t<int> a3 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    constexpr mat3x3_t<int> b3 {3, 2, 1, 6, 5, 4, 9, 8, 7};

    KRYS_EXPECT_TRUE("LessThan Mat3x3 - Scalar", LessThan(a3, 10));
    KRYS_EXPECT_TRUE("LessThanOrEqual Mat3x3 - Scalar", LessThanOrEqual(a3, 9));
    KRYS_EXPECT_FALSE("Equal Mat3x3 - Scalar", Equal(a3, 5));
    KRYS_EXPECT_TRUE("NotEqual Mat3x3 - Scalar", NotEqual(a3, 6));

    // Mat4x4
    constexpr mat4x4_t<int> a4 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    constexpr mat4x4_t<int> b4 {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    KRYS_EXPECT_TRUE("LessThan Mat4x4 - Scalar", LessThan(a4, 20));
    KRYS_EXPECT_TRUE("LessThanOrEqual Mat4x4 - Scalar", LessThanOrEqual(a4, 16));
    KRYS_EXPECT_FALSE("Equal Mat4x4 - Scalar", Equal(a4, 17));
    KRYS_EXPECT_TRUE("NotEqual Mat4x4 - Scalar", NotEqual(a4, 15));
  }
}
