#include "MTL/Vectors/Ext/FMin.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_FMin()
  {
    // Vec1 - 2 arguments
    constexpr vec1_t<float> v1a {1.0f}, v1b {2.0f};
    KRYS_EXPECT_EQUAL("FMin Vec1 (2 args)", FMin(v1a, v1b), (vec1_t<float> {1.0f}));

    // Vec2 - 2 arguments
    constexpr vec2_t<float> v2a {1.0f, 3.0f}, v2b {2.0f, 2.0f};
    KRYS_EXPECT_EQUAL("FMin Vec2 (2 args)", FMin(v2a, v2b), (vec2_t<float> {1.0f, 2.0f}));

    // Vec3 - 2 arguments
    constexpr vec3_t<float> v3a {1.0f, 3.0f, 5.0f}, v3b {2.0f, 2.0f, 4.0f};
    KRYS_EXPECT_EQUAL("FMin Vec3 (2 args)", FMin(v3a, v3b), (vec3_t<float> {1.0f, 2.0f, 4.0f}));

    // Vec4 - 2 arguments
    constexpr vec4_t<float> v4a {1.0f, 3.0f, 5.0f, 7.0f}, v4b {2.0f, 2.0f, 4.0f, 6.0f};
    KRYS_EXPECT_EQUAL("FMin Vec4 (2 args)", FMin(v4a, v4b), (vec4_t<float> {1.0f, 2.0f, 4.0f, 6.0f}));

    // Vec1 - 3 arguments
    constexpr vec1_t<float> v1c {0.5f};
    KRYS_EXPECT_EQUAL("FMin Vec1 (3 args)", FMin(v1a, v1b, v1c), (vec1_t<float> {0.5f}));

    // Vec2 - 3 arguments
    constexpr vec2_t<float> v2c {0.0f, 4.0f};
    KRYS_EXPECT_EQUAL("FMin Vec2 (3 args)", FMin(v2a, v2b, v2c), (vec2_t<float> {0.0f, 2.0f}));

    // Vec3 - 3 arguments
    constexpr vec3_t<float> v3c {0.0f, 1.0f, 3.0f};
    KRYS_EXPECT_EQUAL("FMin Vec3 (3 args)", FMin(v3a, v3b, v3c), (vec3_t<float> {0.0f, 1.0f, 3.0f}));

    // Vec4 - 3 arguments
    constexpr vec4_t<float> v4c {0.0f, 1.0f, 3.0f, 6.0f};
    KRYS_EXPECT_EQUAL("FMin Vec4 (3 args)", FMin(v4a, v4b, v4c), (vec4_t<float> {0.0f, 1.0f, 3.0f, 6.0f}));

    // Vec1 - scalar
    constexpr vec1_t<float> v1s {4.0f};
    KRYS_EXPECT_EQUAL("FMin Vec1 (scalar)", FMin(v1s, 3.0f), (vec1_t<float> {3.0f}));

    // Vec2 - scalar
    constexpr vec2_t<float> v2s {5.0f, 8.0f};
    KRYS_EXPECT_EQUAL("FMin Vec2 (scalar)", FMin(v2s, 6.0f), (vec2_t<float> {5.0f, 6.0f}));

    // Vec3 - scalar
    constexpr vec3_t<float> v3s {8.0f, 11.0f, 6.0f};
    KRYS_EXPECT_EQUAL("FMin Vec3 (scalar)", FMin(v3s, 7.0f), (vec3_t<float> {7.0f, 7.0f, 6.0f}));

    // Vec4 - scalar
    constexpr vec4_t<float> v4s {9.0f, 1.0f, 20.0f, 10.0f};
    KRYS_EXPECT_EQUAL("FMin Vec4 (scalar)", FMin(v4s, 8.0f), (vec4_t<float> {8.0f, 1.0f, 8.0f, 8.0f}));
  }
}
