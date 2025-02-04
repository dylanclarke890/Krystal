#include "MTL/Vectors/Ext/Interpolate.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Vec1_Lerp()
  {
    using vec_t = vec1_t<float>;
    constexpr vec_t x(1.0f);
    constexpr vec_t y(3.0f);

    KRYS_EXPECT_EQUAL("Lerp Vec1 t=0", Lerp(x, y, 0.0f), vec_t(1.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec1 t=0", Lerp(x, y, vec_t(0.0f)), vec_t(1.0f));

    KRYS_EXPECT_EQUAL("Lerp Vec1 t=1", Lerp(x, y, 1.0f), vec_t(3.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec1 t=1", Lerp(x, y, vec_t(1.0f)), vec_t(3.0f));

    KRYS_EXPECT_EQUAL("Lerp Vec1 t=0.5", Lerp(x, y, 0.5f), vec_t(2.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec1 t=0.5", Lerp(x, y, vec_t(0.5f)), vec_t(2.0f));
  }

  static void Test_Vec2_Lerp()
  {
    using vec_t = vec2_t<float>;
    constexpr vec_t x(1.0f, 2.0f);
    constexpr vec_t y(3.0f, 4.0f);

    KRYS_EXPECT_EQUAL("Lerp Vec2 t=0", Lerp(x, y, 0.0f), vec_t(1.0f, 2.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec2 t=0", Lerp(x, y, vec_t(0.0f)), vec_t(1.0f, 2.0f));

    KRYS_EXPECT_EQUAL("Lerp Vec2 t=1", Lerp(x, y, 1.0f), vec_t(3.0f, 4.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec2 t=1", Lerp(x, y, vec_t(1.0f)), vec_t(3.0f, 4.0f));

    KRYS_EXPECT_EQUAL("Lerp Vec2 t=0.5", Lerp(x, y, 0.5f), vec_t(2.0f, 3.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec2 t=0.5", Lerp(x, y, vec_t(0.5f)), vec_t(2.0f, 3.0f));
  }

  static void Test_Vec3_Lerp()
  {
    using vec_t = vec3_t<float>;
    constexpr vec_t x(1.0f, 2.0f, 3.0f);
    constexpr vec_t y(4.0f, 5.0f, 6.0f);

    KRYS_EXPECT_EQUAL("Lerp Vec3 t=0", Lerp(x, y, 0.0f), vec_t(1.0f, 2.0f, 3.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec3 t=0", Lerp(x, y, vec_t(0.0f)), vec_t(1.0f, 2.0f, 3.0f));

    KRYS_EXPECT_EQUAL("Lerp Vec3 t=1", Lerp(x, y, 1.0f), vec_t(4.0f, 5.0f, 6.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec3 t=1", Lerp(x, y, vec_t(1.0f)), vec_t(4.0f, 5.0f, 6.0f));

    KRYS_EXPECT_EQUAL("Lerp Vec3 t=0.5", Lerp(x, y, 0.5f), vec_t(2.5f, 3.5f, 4.5f));
    KRYS_EXPECT_EQUAL("Lerp Vec3 t=0.5", Lerp(x, y, vec_t(0.5f)), vec_t(2.5f, 3.5f, 4.5f));
  }

  static void Test_Vec4_Lerp()
  {
    using vec_t = vec4_t<float>;
    constexpr vec_t x(1.0f, 2.0f, 3.0f, 4.0f);
    constexpr vec_t y(5.0f, 6.0f, 7.0f, 8.0f);

    KRYS_EXPECT_EQUAL("Lerp Vec4 t=0", Lerp(x, y, 0.0f), vec_t(1.0f, 2.0f, 3.0f, 4.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec4 t=0", Lerp(x, y, vec_t(0.0f)), vec_t(1.0f, 2.0f, 3.0f, 4.0f));

    KRYS_EXPECT_EQUAL("Lerp Vec4 t=1", Lerp(x, y, 1.0f), vec_t(5.0f, 6.0f, 7.0f, 8.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec4 t=1", Lerp(x, y, vec_t(1.0f)), vec_t(5.0f, 6.0f, 7.0f, 8.0f));

    KRYS_EXPECT_EQUAL("Lerp Vec4 t=0.5", Lerp(x, y, 0.5f), vec_t(3.0f, 4.0f, 5.0f, 6.0f));
    KRYS_EXPECT_EQUAL("Lerp Vec4 t=0.5", Lerp(x, y, vec_t(0.5f)), vec_t(3.0f, 4.0f, 5.0f, 6.0f));
  }
}
