#include "MTL/Vectors/Ext/Degrees.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;
  constexpr float PI = Pi<float>();

  static void Test_Vec1_Degrees()
  {
    using vec_t = vec1_t<float>;

    constexpr vec_t vec(PI);
    KRYS_EXPECT_EQUAL("Degrees Vec1", Degrees(vec), vec_t(180.0f));
  }

  static void Test_Vec2_Degrees()
  {
    using vec_t = vec2_t<float>;

    constexpr vec_t vec(PI, PI / 2);
    KRYS_EXPECT_EQUAL("Degrees Vec2", Degrees(vec), vec_t(180, 90));
  }

  static void Test_Vec3_Degrees()
  {
    using vec_t = vec3_t<float>;

    constexpr vec_t vec(PI, PI / 2, PI / 3);
    KRYS_EXPECT_EQUAL("Degrees Vec3", Degrees(vec), vec_t(180, 90, 60));
  }

  static void Test_Vec4_Degrees()
  {
    using vec_t = vec4_t<float>;

    constexpr vec_t vec(PI, PI / 2, PI / 3, PI / 4);
    KRYS_EXPECT_EQUAL("Degrees Vec4", Degrees(vec), vec_t(180, 90, 60, 45));
  }
}
