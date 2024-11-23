#include "MTL/Vectors/Ext/Common/Radians.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Radians()
  {
    // Vec1
    constexpr vec1_t<float> v1 {180.0f};
    KRYS_EXPECT_EQUAL("Radians Vec1", Radians(v1), (vec1_t<float> {MTL::Pi<float>()}));

    // Vec2
    constexpr vec2_t<float> v2 {90.0f, 360.0f};
    KRYS_EXPECT_EQUAL("Radians Vec2", Radians(v2),
                      (vec2_t<float> {MTL::Pi<float>() / 2.0f, 2.0f * MTL::Pi<float>()}));

    // Vec3
    constexpr vec3_t<float> v3 {45.0f, 180.0f, 270.0f};
    KRYS_EXPECT_EQUAL(
      "Radians Vec3", Radians(v3),
      (vec3_t<float> {MTL::Pi<float>() / 4.0f, MTL::Pi<float>(), 3.0f * MTL::Pi<float>() / 2.0f}));

    // Vec4
    constexpr vec4_t<float> v4 {0.0f, 30.0f, 60.0f, 360.0f};
    KRYS_EXPECT_EQUAL(
      "Radians Vec4", Radians(v4),
      (vec4_t<float> {0.0f, MTL::Pi<float>() / 6.0f, MTL::Pi<float>() / 3.0f, 2.0f * MTL::Pi<float>()}));
  }
}
