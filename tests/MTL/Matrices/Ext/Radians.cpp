#include "MTL/Matrices/Ext/Radians.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Radians()
  {
    constexpr float PI = MTL::Pi<float>();
    // mat2x2
    constexpr mat2x2_t<float> v1 {30.0f, 45.0f, 60.0f, 90.0f};
    constexpr mat2x2_t<float> expected1 {PI / 6.0f, PI / 4.0f, PI / 3.0f, PI / 2.0f};
    constexpr mat2x2_t<float> result1 = Radians(v1);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat2x2 (0,0)", result1[0].x, expected1[0].x, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat2x2 (0,1)", result1[0].y, expected1[0].y, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat2x2 (1,0)", result1[1].x, expected1[1].x, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat2x2 (1,1)", result1[1].y, expected1[1].y, 1e-6f);

    // mat3x3
    constexpr mat3x3_t<float> v2 {0.0f, 180.0f, -90.0f, 45.0f, -60.0f, 360.0f, -30.0f, 135.0f, 22.5f};
    constexpr mat3x3_t<float> expected2 {0.0f,      PI,         -PI / 2.0f,       PI / 4.0f, -PI / 3.0f,
                                         2.0f * PI, -PI / 6.0f, 3.0f * PI / 4.0f, PI / 8.0f};
    constexpr auto result2 = Radians(v2);
    // Manually verify x, y, z for mat3x3
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat3x3 (0,0)", result2[0].x, expected2[0].x, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat3x3 (0,1)", result2[0].y, expected2[0].y, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat3x3 (0,2)", result2[0].z, expected2[0].z, 1e-6f);

    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat3x3 (1,0)", result2[1].x, expected2[1].x, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat3x3 (1,1)", result2[1].y, expected2[1].y, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat3x3 (1,2)", result2[1].z, expected2[1].z, 1e-6f);

    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat3x3 (2,0)", result2[2].x, expected2[2].x, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat3x3 (2,1)", result2[2].y, expected2[2].y, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat3x3 (2,2)", result2[2].z, expected2[2].z, 1e-6f);

    // mat4x4
    constexpr mat4x4_t<float> v3 {0.0f,  90.0f,  180.0f,  270.0f,  45.0f,  -30.0f, 360.0f,  -60.0f,
                                  22.5f, 135.0f, -180.0f, -135.0f, 150.0f, 157.5f, -157.5f, -150.0f};
    constexpr mat4x4_t<float> expected3 {0.0f,
                                         PI / 2.0f,
                                         PI,
                                         3.0f * PI / 2.0f,
                                         PI / 4.0f,
                                         -PI / 6.0f,
                                         2.0f * PI,
                                         -PI / 3.0f,
                                         PI / 8.0f,
                                         3.0f * PI / 4.0f,
                                         -PI,
                                         -3.0f * PI / 4.0f,
                                         5.0f * PI / 6.0f,
                                         7.0f * PI / 8.0f,
                                         -7.0f * PI / 8.0f,
                                         -5.0f * PI / 6.0f};
    constexpr auto result3 = Radians(v3);
    // Manually verify x, y, z, w for mat4x4
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (0,0)", result3[0].x, expected3[0].x, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (0,1)", result3[0].y, expected3[0].y, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (0,2)", result3[0].z, expected3[0].z, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (0,3)", result3[0].w, expected3[0].w, 1e-6f);

    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (1,0)", result3[1].x, expected3[1].x, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (1,1)", result3[1].y, expected3[1].y, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (1,2)", result3[1].z, expected3[1].z, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (1,3)", result3[1].w, expected3[1].w, 1e-6f);

    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (2,0)", result3[2].x, expected3[2].x, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (2,1)", result3[2].y, expected3[2].y, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (2,2)", result3[2].z, expected3[2].z, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (2,3)", result3[2].w, expected3[2].w, 1e-6f);

    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (3,0)", result3[3].x, expected3[3].x, 1e-5f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (3,1)", result3[3].y, expected3[3].y, 1e-5f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (3,2)", result3[3].z, expected3[3].z, 1e-5f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians Mat4x4 (3,3)", result3[3].w, expected3[3].w, 1e-5f);
  }
}
