#include "MTL/Vectors/Ext/Common/Ceil.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Ceil()
  {
    // Vec1
    constexpr vec1_t<float> v1 {1.1f};
    KRYS_EXPECT_EQUAL("Ceil Vec1", Ceil(v1), (vec1_t<float> {2.0f}));

    // Vec2
    constexpr vec2_t<float> v2 {1.1f, -2.3f};
    KRYS_EXPECT_EQUAL("Ceil Vec2", Ceil(v2), (vec2_t<float> {2.0f, -2.0f}));

    // Vec3
    constexpr vec3_t<float> v3 {1.1f, -2.3f, 3.7f};
    KRYS_EXPECT_EQUAL("Ceil Vec3", Ceil(v3), (vec3_t<float> {2.0f, -2.0f, 4.0f}));

    // Vec4
    constexpr vec4_t<float> v4 {1.1f, -2.3f, 3.7f, 4.5f};
    KRYS_EXPECT_EQUAL("Ceil Vec4", Ceil(v4), (vec4_t<float> {2.0f, -2.0f, 4.0f, 5.0f}));
  }
}
