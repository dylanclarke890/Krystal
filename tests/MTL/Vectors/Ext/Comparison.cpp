#include "MTL/Vectors/Ext/Comparison.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_LessThan()
  {
    // Vec1
    constexpr vec1_t<int> a1 {1}, b1 {2};
    constexpr vec1_t<bool> result1 = LessThan(a1, b1);
    KRYS_EXPECT_TRUE("LessThan Vec1 - Vec", result1.x);
    KRYS_EXPECT_TRUE("LessThan Vec1 - Scalar", LessThan(a1, 3));

    // Vec2
    constexpr vec2_t<int> a2 {1, 3}, b2 {2, 2};
    constexpr vec2_t<bool> result2 = LessThan(a2, b2);
    KRYS_EXPECT_TRUE("LessThan Vec2.x", result2.x);
    KRYS_EXPECT_FALSE("LessThan Vec2.y", result2.y);
    KRYS_EXPECT_TRUE("LessThan Vec2 - Scalar", LessThan(a2, 4));

    // Vec3
    constexpr vec3_t<int> a3 {1, 3, 5}, b3 {2, 2, 6};
    constexpr vec3_t<bool> result3 = LessThan(a3, b3);
    KRYS_EXPECT_TRUE("LessThan Vec3.x", result3.x);
    KRYS_EXPECT_FALSE("LessThan Vec3.y", result3.y);
    KRYS_EXPECT_TRUE("LessThan Vec3.z", result3.z);
    KRYS_EXPECT_TRUE("LessThan Vec3 - Scalar", LessThan(a3, 6));

    // Vec4
    constexpr vec4_t<int> a4 {1, 3, 5, 7}, b4 {2, 2, 6, 6};
    constexpr vec4_t<bool> result4 = LessThan(a4, b4);
    KRYS_EXPECT_TRUE("LessThan Vec4.x", result4.x);
    KRYS_EXPECT_FALSE("LessThan Vec4.y", result4.y);
    KRYS_EXPECT_TRUE("LessThan Vec4.z", result4.z);
    KRYS_EXPECT_FALSE("LessThan Vec4.w", result4.w);
    KRYS_EXPECT_TRUE("LessThan Vec4 - Scalar", LessThan(a4, 8));
  }

  static void Test_LessThanOrEqual()
  {
    // Vec1
    constexpr vec1_t<int> a1 {2}, b1 {2};
    constexpr vec1_t<bool> result1 = LessThanOrEqual(a1, b1);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec1 - Vec", result1.x);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec1 - Scalar", LessThanOrEqual(a1, 3));

    // Vec2
    constexpr vec2_t<int> a2 {1, 3}, b2 {2, 3};
    constexpr vec2_t<bool> result2 = LessThanOrEqual(a2, b2);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec2.x", result2.x);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec2.y", result2.y);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec2 - Scalar", LessThanOrEqual(a2, 4));

    // Vec3
    constexpr vec3_t<int> a3 {1, 3, 5}, b3 {2, 3, 5};
    constexpr vec3_t<bool> result3 = LessThanOrEqual(a3, b3);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec3.x", result3.x);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec3.y", result3.y);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec3.z", result3.z);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec3 - Scalar", LessThanOrEqual(a3, 6));

    // Vec4
    constexpr vec4_t<int> a4 {1, 3, 5, 7}, b4 {2, 3, 6, 7};
    constexpr vec4_t<bool> result4 = LessThanOrEqual(a4, b4);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec4.x", result4.x);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec4.y", result4.y);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec4.z", result4.z);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec4.w", result4.w);
    KRYS_EXPECT_TRUE("LessThanOrEqual Vec4 - Scalar", LessThanOrEqual(a4, 8));
  }

  static void Test_Equal()
  {
    // Vec1
    constexpr vec1_t<int> a1 {1}, b1 {1};
    constexpr vec1_t<bool> result1 = Equal(a1, b1);
    KRYS_EXPECT_TRUE("Equal Vec1 - Vec", result1.x);
    KRYS_EXPECT_TRUE("Equal Vec1 - Scalar", Equal(a1, 1));

    // Vec2
    constexpr vec2_t<int> a2 {1, 3}, b2 {1, 3};
    constexpr vec2_t<bool> result2 = Equal(a2, b2);
    KRYS_EXPECT_TRUE("Equal Vec2.x", result2.x);
    KRYS_EXPECT_TRUE("Equal Vec2.y", result2.y);
    KRYS_EXPECT_FALSE("Equal Vec2 - Scalar", Equal(a2, 4));

    // Vec3
    constexpr vec3_t<int> a3 {1, 3, 5}, b3 {1, 3, 5};
    constexpr vec3_t<bool> result3 = Equal(a3, b3);
    KRYS_EXPECT_TRUE("Equal Vec3.x", result3.x);
    KRYS_EXPECT_TRUE("Equal Vec3.y", result3.y);
    KRYS_EXPECT_TRUE("Equal Vec3.z", result3.z);
    KRYS_EXPECT_FALSE("Equal Vec3 - Scalar", Equal(a3, 6));

    // Vec4
    constexpr vec4_t<int> a4 {1, 3, 5, 7}, b4 {1, 3, 5, 7};
    constexpr vec4_t<bool> result4 = Equal(a4, b4);
    KRYS_EXPECT_TRUE("Equal Vec4.x", result4.x);
    KRYS_EXPECT_TRUE("Equal Vec4.y", result4.y);
    KRYS_EXPECT_TRUE("Equal Vec4.z", result4.z);
    KRYS_EXPECT_TRUE("Equal Vec4.w", result4.w);
    KRYS_EXPECT_FALSE("Equal Vec4 - Scalar", Equal(a4, 8));
  }

  static void Test_NotEqual()
  {
    // Vec1
    constexpr vec1_t<int> a1 {1}, b1 {2};
    constexpr vec1_t<bool> result1 = NotEqual(a1, b1);
    KRYS_EXPECT_TRUE("NotEqual Vec1 - Vec", result1.x);
    KRYS_EXPECT_TRUE("NotEqual Vec1 - Scalar", NotEqual(a1, 2));

    // Vec2
    constexpr vec2_t<int> a2 {1, 3}, b2 {1, 2};
    constexpr vec2_t<bool> result2 = NotEqual(a2, b2);
    KRYS_EXPECT_FALSE("NotEqual Vec2.x", result2.x);
    KRYS_EXPECT_TRUE("NotEqual Vec2.y", result2.y);
    KRYS_EXPECT_TRUE("NotEqual Vec2 - Scalar", NotEqual(a2, 4));

    // Vec3
    constexpr vec3_t<int> a3 {1, 3, 5}, b3 {1, 2, 5};
    constexpr vec3_t<bool> result3 = NotEqual(a3, b3);
    KRYS_EXPECT_FALSE("NotEqual Vec3.x", result3.x);
    KRYS_EXPECT_TRUE("NotEqual Vec3.y", result3.y);
    KRYS_EXPECT_FALSE("NotEqual Vec3.z", result3.z);
    KRYS_EXPECT_TRUE("NotEqual Vec3 - Scalar", NotEqual(a3, 6));

    // Vec4
    constexpr vec4_t<int> a4 {1, 3, 5, 7}, b4 {1, 3, 5, 7};
    constexpr vec4_t<bool> result4 = NotEqual(a4, b4);
    KRYS_EXPECT_FALSE("NotEqual Vec4.x", result4.x);
    KRYS_EXPECT_FALSE("NotEqual Vec4.y", result4.y);
    KRYS_EXPECT_FALSE("NotEqual Vec4.z", result4.z);
    KRYS_EXPECT_FALSE("NotEqual Vec4.w", result4.w);
    KRYS_EXPECT_TRUE("NotEqual Vec4 - Scalar", NotEqual(a4, 8));
  }
}
