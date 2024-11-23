#include "MTL/Vectors/Ext/Common/Floor.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Floor()
  {
    // Vec1
    constexpr vec1_t<float> v1 {1.9f};
    KRYS_EXPECT_EQUAL("Floor Vec1", Floor(v1), (vec1_t<float> {1.0f}));

    // Vec2
    constexpr vec2_t<float> v2 {1.9f, -2.1f};
    KRYS_EXPECT_EQUAL("Floor Vec2", Floor(v2), (vec2_t<float> {1.0f, -3.0f}));

    // Vec3
    constexpr vec3_t<float> v3 {1.9f, -2.1f, 3.7f};
    KRYS_EXPECT_EQUAL("Floor Vec3", Floor(v3), (vec3_t<float> {1.0f, -3.0f, 3.0f}));

    // Vec4
    constexpr vec4_t<float> v4 {1.9f, -2.1f, 3.7f, -4.8f};
    KRYS_EXPECT_EQUAL("Floor Vec4", Floor(v4), (vec4_t<float> {1.0f, -3.0f, 3.0f, -5.0f}));
  }
}
