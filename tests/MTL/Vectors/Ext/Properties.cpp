#include "MTL/Vectors/Ext/Properties.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Vec_AreCollinear()
  {
    using vec2 = vector_t<float, 2>;
    using vec3 = vector_t<float, 3>;
    using vec4 = vector_t<float, 4>;
    constexpr float epsilon = 1e-6f;

    KRYS_EXPECT_TRUE("AreCollinear Vec2", AreCollinear(vec2(1, 2), vec2(2, 4), epsilon));
    KRYS_EXPECT_FALSE("AreCollinear Vec2", AreCollinear(vec2(1, 2), vec2(3, 5), epsilon));

    KRYS_EXPECT_TRUE("AreCollinear Vec3", AreCollinear(vec3(1, 2, 3), vec3(2, 4, 6), epsilon));
    KRYS_EXPECT_FALSE("AreCollinear Vec3", AreCollinear(vec3(1, 2, 3), vec3(3, 5, 7), epsilon));

    KRYS_EXPECT_TRUE("AreCollinear Vec4", AreCollinear(vec4(1, 2, 3, 0), vec4(2, 4, 6, 0), epsilon));
    KRYS_EXPECT_FALSE("AreCollinear Vec4", AreCollinear(vec4(1, 2, 3, 0), vec4(3, 5, 7, 1), epsilon));
  }

  static void Test_Vec_AreOrthogonal()
  {
    using vec2 = vector_t<float, 2>;
    using vec3 = vector_t<float, 3>;
    using vec4 = vector_t<float, 4>;
    constexpr float epsilon = 1e-6f;

    KRYS_EXPECT_TRUE("AreOrthogonal Vec2", AreOrthogonal(vec2(1, 0), vec2(0, 1), epsilon));
    KRYS_EXPECT_FALSE("AreOrthogonal Vec2", AreOrthogonal(vec2(1, 1), vec2(0, 1), epsilon));

    KRYS_EXPECT_TRUE("AreOrthogonal Vec3", AreOrthogonal(vec3(1, 0, 0), vec3(0, 1, 0), epsilon));
    KRYS_EXPECT_FALSE("AreOrthogonal Vec3", AreOrthogonal(vec3(1, 1, 1), vec3(0, 1, 0), epsilon));

    KRYS_EXPECT_TRUE("AreOrthogonal Vec4", AreOrthogonal(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), epsilon));
    KRYS_EXPECT_FALSE("AreOrthogonal Vec4", AreOrthogonal(vec4(1, 1, 1, 1), vec4(0, 1, 0, 0), epsilon));
  }

  static void Test_Vec_IsNormalized()
  {
    using vec2 = vector_t<float, 2>;
    using vec3 = vector_t<float, 3>;
    using vec4 = vector_t<float, 4>;
    constexpr float epsilon = 1e-6f;

    KRYS_EXPECT_TRUE("IsNormalized Vec2", IsNormalized(vec2(1, 0), epsilon));
    KRYS_EXPECT_FALSE("IsNormalized Vec2", IsNormalized(vec2(2, 0), epsilon));

    KRYS_EXPECT_TRUE("IsNormalized Vec3", IsNormalized(vec3(1, 0, 0), epsilon));
    KRYS_EXPECT_FALSE("IsNormalized Vec3", IsNormalized(vec3(2, 0, 0), epsilon));

    KRYS_EXPECT_TRUE("IsNormalized Vec4", IsNormalized(vec4(1, 0, 0, 0), epsilon));
    KRYS_EXPECT_FALSE("IsNormalized Vec4", IsNormalized(vec4(2, 0, 0, 0), epsilon));
  }

  static void Test_Vec_IsNull()
  {
    using vec2 = vector_t<float, 2>;
    using vec3 = vector_t<float, 3>;
    using vec4 = vector_t<float, 4>;
    constexpr float epsilon = 1e-6f;

    KRYS_EXPECT_TRUE("IsNull Vec2", IsNull(vec2(0, 0), epsilon));
    KRYS_EXPECT_FALSE("IsNull Vec2", IsNull(vec2(1, 0), epsilon));

    KRYS_EXPECT_TRUE("IsNull Vec3", IsNull(vec3(0, 0, 0), epsilon));
    KRYS_EXPECT_FALSE("IsNull Vec3", IsNull(vec3(1, 0, 0), epsilon));

    KRYS_EXPECT_TRUE("IsNull Vec4", IsNull(vec4(0, 0, 0, 0), epsilon));
    KRYS_EXPECT_FALSE("IsNull Vec4", IsNull(vec4(1, 0, 0, 0), epsilon));
  }

  static void Test_Vec_AreOrthonormal()
  {
    using vec2 = vector_t<float, 2>;
    using vec3 = vector_t<float, 3>;
    using vec4 = vector_t<float, 4>;
    constexpr float epsilon = 1e-6f;

    KRYS_EXPECT_TRUE("AreOrthonormal Vec2", AreOrthonormal(vec2(1, 0), vec2(0, 1), epsilon));
    KRYS_EXPECT_FALSE("AreOrthonormal Vec2", AreOrthonormal(vec2(1, 1), vec2(0, 1), epsilon));

    KRYS_EXPECT_TRUE("AreOrthonormal Vec3", AreOrthonormal(vec3(1, 0, 0), vec3(0, 1, 0), epsilon));
    KRYS_EXPECT_FALSE("AreOrthonormal Vec3", AreOrthonormal(vec3(1, 1, 1), vec3(0, 1, 0), epsilon));

    KRYS_EXPECT_TRUE("AreOrthonormal Vec4", AreOrthonormal(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), epsilon));
    KRYS_EXPECT_FALSE("AreOrthonormal Vec4", AreOrthonormal(vec4(1, 1, 1, 1), vec4(0, 1, 0, 0), epsilon));
  }
}
