#include "MTL/Vectors/Ext/Convert.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;
  constexpr float PI = Pi<float>();

#pragma region Degrees

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

#pragma endregion Degrees

#pragma region Radians

  static void Test_Vec1_Radians()
  {
    using vec_t = Vec1;
    constexpr vec_t vec(180);

    KRYS_EXPECT_EQUAL("Radians Vec1", Radians(vec), vec_t(PI));
  }

  static void Test_Vec2_Radians()
  {
    using vec_t = Vec2;
    constexpr vec_t vec(180, 90);

    KRYS_EXPECT_EQUAL("Radians Vec2", Radians(vec), vec_t(PI, PI / 2));
  }

  static void Test_Vec3_Radians()
  {
    using vec_t = Vec3;
    constexpr vec_t vec(180, 90, 60);

    KRYS_EXPECT_EQUAL("Radians Vec3", Radians(vec), vec_t(PI, PI / 2, PI / 3));
  }

  static void Test_Vec4_Radians()
  {
    using vec_t = Vec4;
    constexpr vec_t vec(180, 90, 60, 45);

    KRYS_EXPECT_EQUAL("Radians Vec4", Radians(vec), vec_t(PI, PI / 2, PI / 3, PI / 4));
  }

#pragma endregion Radians
}
