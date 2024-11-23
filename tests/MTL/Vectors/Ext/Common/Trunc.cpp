#include "MTL/Vectors/Ext/Common/Trunc.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Trunc()
  {
    // Vec1
    constexpr vec1_t<float> v1 {5.7f};
    KRYS_EXPECT_EQUAL("Trunc Vec1", Trunc(v1), (vec1_t<float> {5.0f}));

    // Vec2
    constexpr vec2_t<float> v2 {5.7f, -8.3f};
    KRYS_EXPECT_EQUAL("Trunc Vec2", Trunc(v2), (vec2_t<float> {5.0f, -8.0f}));

    // Vec3
    constexpr vec3_t<float> v3 {5.7f, -8.3f, 14.99f};
    KRYS_EXPECT_EQUAL("Trunc Vec3", Trunc(v3), (vec3_t<float> {5.0f, -8.0f, 14.0f}));

    // Vec4
    constexpr vec4_t<float> v4 {5.7f, -8.3f, 14.99f, -20.75f};
    KRYS_EXPECT_EQUAL("Trunc Vec4", Trunc(v4), (vec4_t<float> {5.0f, -8.0f, 14.0f, -20.0f}));
  }
}
