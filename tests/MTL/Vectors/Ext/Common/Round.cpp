#include "MTL/Vectors/Ext/Common/Round.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Round()
  {
    // Vec1
    constexpr vec1_t<float> v1 {5.7f};
    KRYS_EXPECT_EQUAL("Round Vec1", Round(v1), (vec1_t<float> {6.0f}));

    // Vec2
    constexpr vec2_t<float> v2 {5.4f, -8.6f};
    KRYS_EXPECT_EQUAL("Round Vec2", Round(v2), (vec2_t<float> {5.0f, -9.0f}));

    // Vec3
    constexpr vec3_t<float> v3 {5.5f, -8.3f, 14.49f};
    KRYS_EXPECT_EQUAL("Round Vec3", Round(v3), (vec3_t<float> {6.0f, -8.0f, 14.0f}));

    // Vec4
    constexpr vec4_t<float> v4 {5.75f, -8.25f, 14.5f, -20.75f};
    KRYS_EXPECT_EQUAL("Round Vec4", Round(v4), (vec4_t<float> {6.0f, -8.0f, 15.0f, -21.0f}));
  }
}
