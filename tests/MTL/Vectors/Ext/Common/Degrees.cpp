#include "MTL/Vectors/Ext/Common/Degrees.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Degrees()
  {
    // Vec1
    constexpr vec1_t<float> v1 {3.141592653589793f}; // PI radians
    KRYS_EXPECT_EQUAL("Degrees Vec1", Degrees(v1), (vec1_t<float> {180.0f}));

    // Vec2
    constexpr vec2_t<float> v2 {1.5707963267948966f, 3.141592653589793f}; // PI/2 and PI radians
    KRYS_EXPECT_EQUAL("Degrees Vec2", Degrees(v2), (vec2_t<float> {90.0f, 180.0f}));

    // Vec3
    constexpr vec3_t<float> v3 {0.0f, 1.5707963267948966f, 3.141592653589793f}; // 0, PI/2, and PI radians
    KRYS_EXPECT_EQUAL("Degrees Vec3", Degrees(v3), (vec3_t<float> {0.0f, 90.0f, 180.0f}));

    // Vec4
    constexpr vec4_t<float> v4 {0.0f, 1.5707963267948966f, 3.141592653589793f,
                                4.71238898038469f}; // 0, PI/2, PI, 3PI/2 radians
    KRYS_EXPECT_EQUAL("Degrees Vec4", Degrees(v4), (vec4_t<float> {0.0f, 90.0f, 180.0f, 270.0f}));
  }
}
