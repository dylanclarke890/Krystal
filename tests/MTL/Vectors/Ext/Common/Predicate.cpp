#include "MTL/Vectors/Ext/Common/Predicate.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_AnyOf()
  {
    // Vec1
    constexpr vec1_t<int> v1 {1};
    KRYS_EXPECT_TRUE("AnyOf Vec1 (True)", AnyOf(v1, [](int value) { return value > 0; }));
    KRYS_EXPECT_FALSE("AnyOf Vec1 (False)", AnyOf(v1, [](int value) { return value < 0; }));

    // Vec2
    constexpr vec2_t<int> v2 {1, -1};
    KRYS_EXPECT_TRUE("AnyOf Vec2 (True)", AnyOf(v2, [](int value) { return value < 0; }));
    KRYS_EXPECT_FALSE("AnyOf Vec2 (False)", AnyOf(v2, [](int value) { return value > 10; }));

    // Vec3
    constexpr vec3_t<int> v3 {1, 2, 3};
    KRYS_EXPECT_TRUE("AnyOf Vec3 (True)", AnyOf(v3, [](int value) { return value == 2; }));
    KRYS_EXPECT_FALSE("AnyOf Vec3 (False)", AnyOf(v3, [](int value) { return value < 0; }));

    // Vec4
    constexpr vec4_t<int> v4 {0, -1, 2, 3};
    KRYS_EXPECT_TRUE("AnyOf Vec4 (True)", AnyOf(v4, [](int value) { return value < 0; }));
    KRYS_EXPECT_FALSE("AnyOf Vec4 (False)", AnyOf(v4, [](int value) { return value > 10; }));
  }

  static void Test_AllOf()
  {
    // Vec1
    constexpr vec1_t<int> v1 {1};
    KRYS_EXPECT_TRUE("AllOf Vec1 (True)", AllOf(v1, [](int value) { return value > 0; }));
    KRYS_EXPECT_FALSE("AllOf Vec1 (False)", AllOf(v1, [](int value) { return value < 0; }));

    // Vec2
    constexpr vec2_t<int> v2 {1, -1};
    KRYS_EXPECT_FALSE("AllOf Vec2 (False)", AllOf(v2, [](int value) { return value > 0; }));
    KRYS_EXPECT_TRUE("AllOf Vec2 (True)", AllOf(v2, [](int value) { return value != 0; }));

    // Vec3
    constexpr vec3_t<int> v3 {1, 2, 3};
    KRYS_EXPECT_TRUE("AllOf Vec3 (True)", AllOf(v3, [](int value) { return value > 0; }));
    KRYS_EXPECT_FALSE("AllOf Vec3 (False)", AllOf(v3, [](int value) { return value < 3; }));

    // Vec4
    constexpr vec4_t<int> v4 {0, 1, 2, 3};
    KRYS_EXPECT_FALSE("AllOf Vec4 (False)", AllOf(v4, [](int value) { return value > 0; }));
    KRYS_EXPECT_TRUE("AllOf Vec4 (True)", AllOf(v4, [](int value) { return value <= 3; }));
  }

  static void Test_NoneOf()
  {
    // Vec1
    constexpr vec1_t<int> v1 {1};
    KRYS_EXPECT_TRUE("NoneOf Vec1 (True)", NoneOf(v1, [](int value) { return value < 0; }));
    KRYS_EXPECT_FALSE("NoneOf Vec1 (False)", NoneOf(v1, [](int value) { return value > 0; }));

    // Vec2
    constexpr vec2_t<int> v2 {1, -1};
    KRYS_EXPECT_FALSE("NoneOf Vec2 (False)", NoneOf(v2, [](int value) { return value < 0; }));
    KRYS_EXPECT_TRUE("NoneOf Vec2 (True)", NoneOf(v2, [](int value) { return value > 10; }));

    // Vec3
    constexpr vec3_t<int> v3 {1, 2, 3};
    KRYS_EXPECT_TRUE("NoneOf Vec3 (True)", NoneOf(v3, [](int value) { return value < 0; }));
    KRYS_EXPECT_FALSE("NoneOf Vec3 (False)", NoneOf(v3, [](int value) { return value == 2; }));

    // Vec4
    constexpr vec4_t<int> v4 {0, -1, 2, 3};
    KRYS_EXPECT_FALSE("NoneOf Vec4 (False)", NoneOf(v4, [](int value) { return value < 0; }));
    KRYS_EXPECT_TRUE("NoneOf Vec4 (True)", NoneOf(v4, [](int value) { return value > 10; }));
  }
}
