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
    KRYS_EXPECT_EQUAL("LessThanOrEqual Mat2x2", LessThanOrEqual(a2, b2), expected_le2);
    KRYS_EXPECT_EQUAL("Equal Mat2x2", Equal(a2, b2), expected_eq2);
    KRYS_EXPECT_EQUAL("NotEqual Mat2x2", NotEqual(a2, b2), expected_ne2);
    KRYS_EXPECT_EQUAL("GreaterThan Mat2x2", GreaterThan(a2, b2), expected_gt2);
    KRYS_EXPECT_EQUAL("GreaterThanOrEqual Mat2x2", GreaterThanOrEqual(a2, b2), expected_ge2);

    // Mat3x3
    constexpr mat3x3_t<int> a3 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    constexpr mat3x3_t<int> b3 {3, 2, 1, 6, 5, 4, 9, 8, 7};

    constexpr mat3x3_t<bool> expected_lt3 {true, false, false, true, false, false, true, false, false};
    constexpr mat3x3_t<bool> expected_le3 {true, true, false, true, true, false, true, true, false};
    constexpr mat3x3_t<bool> expected_eq3 {false, true, false, false, true, false, false, true, false};
    constexpr mat3x3_t<bool> expected_ne3 {true, false, true, true, false, true, true, false, true};
    constexpr mat3x3_t<bool> expected_gt3 {false, false, true, false, false, true, false, false, true};
    constexpr mat3x3_t<bool> expected_ge3 {false, true, true, false, true, true, false, true, true};

    KRYS_EXPECT_EQUAL("LessThan Mat3x3", LessThan(a3, b3), expected_lt3);
    KRYS_EXPECT_EQUAL("LessThanOrEqual Mat3x3", LessThanOrEqual(a3, b3), expected_le3);
    KRYS_EXPECT_EQUAL("Equal Mat3x3", Equal(a3, b3), expected_eq3);
    KRYS_EXPECT_EQUAL("NotEqual Mat3x3", NotEqual(a3, b3), expected_ne3);
    KRYS_EXPECT_EQUAL("GreaterThan Mat3x3", GreaterThan(a3, b3), expected_gt3);
    KRYS_EXPECT_EQUAL("GreaterThanOrEqual Mat3x3", GreaterThanOrEqual(a3, b3), expected_ge3);

    // Mat4x4
    constexpr mat4x4_t<int> a4 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    constexpr mat4x4_t<int> b4 {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    constexpr mat4x4_t<bool> expected_lt4 {true,  true,  true,  true,  true,  true,  true,  true,
                                           false, false, false, false, false, false, false, false};
    constexpr mat4x4_t<bool> expected_le4 {true,  true,  true,  true,  true,  true,  true,  true,
                                           false, false, false, false, false, false, false, false};
    constexpr mat4x4_t<bool> expected_eq4 {false, false, false, false, false, false, false, false,
                                           false, false, false, false, false, false, false, false};
    constexpr mat4x4_t<bool> expected_ne4 {true, true, true, true, true, true, true, true,
                                           true, true, true, true, true, true, true, true};
    constexpr mat4x4_t<bool> expected_gt4 {false, false, false, false, false, false, false, false,
                                           true,  true,  true,  true,  true,  true,  true,  true};
    constexpr mat4x4_t<bool> expected_ge4 {false, false, false, false, false, false, false, false,
                                           true,  true,  true,  true,  true,  true,  true,  true};

    KRYS_EXPECT_EQUAL("LessThan Mat4x4", LessThan(a4, b4), expected_lt4);
    KRYS_EXPECT_EQUAL("LessThanOrEqual Mat4x4", LessThanOrEqual(a4, b4), expected_le4);
    KRYS_EXPECT_EQUAL("Equal Mat4x4", Equal(a4, b4), expected_eq4);
    KRYS_EXPECT_EQUAL("NotEqual Mat4x4", NotEqual(a4, b4), expected_ne4);
    KRYS_EXPECT_EQUAL("GreaterThan Mat4x4", GreaterThan(a4, b4), expected_gt4);
    KRYS_EXPECT_EQUAL("GreaterThanOrEqual Mat4x4", GreaterThanOrEqual(a4, b4), expected_ge4);
  }
}
