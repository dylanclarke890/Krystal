#include "MTL/Vectors/Ext/Abs.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Abs()
  {
    // Vec1
    constexpr vec1_t<int> v1i {-1};
    constexpr vec1_t<float> v1f {-1.0f};
    KRYS_EXPECT_EQUAL("Abs Vec1i", Abs(v1i), (vec1_t<int> {1}));
    KRYS_EXPECT_EQUAL("Abs Vec1f", Abs(v1f), (vec1_t<float> {1.0f}));

    // Vec2
    constexpr vec2_t<int> v2i {-1, -2};
    constexpr vec2_t<float> v2f {-1, -2};
    KRYS_EXPECT_EQUAL("Abs Vec2i", Abs(v2i), (vec2_t<int> {1, 2}));
    KRYS_EXPECT_EQUAL("Abs Vec2f", Abs(v2f), (vec2_t<float> {1.0f, 2.0f}));

    // Vec3
    constexpr vec3_t<int> v3i {-1, -2, -3};
    constexpr vec3_t<float> v3f {-1.0f, -2.0f, -3.0f};
    KRYS_EXPECT_EQUAL("Abs Vec3i", Abs(v3i), (vec3_t<int> {1, 2, 3}));
    KRYS_EXPECT_EQUAL("Abs Vec3f", Abs(v3f), (vec3_t<float> {1.0f, 2.0f, 3.0f}));

    // Vec4
    constexpr vec4_t<int> v4i {-1, -2, -3, -4};
    constexpr vec4_t<float> v4f {-1.0f, -2.0f, -3.0f, -4.0f};
    KRYS_EXPECT_EQUAL("Abs Vec4i", Abs(v4i), (vec4_t<int> {1, 2, 3, 4}));
    KRYS_EXPECT_EQUAL("Abs Vec4f", Abs(v4f), (vec4_t<float> {1.0f, 2.0f, 3.0f, 4.0f}));
  }
}