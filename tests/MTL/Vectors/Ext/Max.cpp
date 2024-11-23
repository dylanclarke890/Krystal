#include "MTL/Vectors/Ext/Max.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Max()
  {
    // Vec1 - 2 arguments
    constexpr vec1_t<int> v1a {1}, v1b {2};
    KRYS_EXPECT_EQUAL("Max Vec1 (2 args)", Max(v1a, v1b), (vec1_t<int> {2}));

    // Vec2 - 2 arguments
    constexpr vec2_t<int> v2a {1, 3}, v2b {2, 2};
    KRYS_EXPECT_EQUAL("Max Vec2 (2 args)", Max(v2a, v2b), (vec2_t<int> {2, 3}));

    // Vec3 - 2 arguments
    constexpr vec3_t<int> v3a {1, 3, 5}, v3b {2, 2, 4};
    KRYS_EXPECT_EQUAL("Max Vec3 (2 args)", Max(v3a, v3b), (vec3_t<int> {2, 3, 5}));

    // Vec4 - 2 arguments
    constexpr vec4_t<int> v4a {1, 3, 5, 7}, v4b {2, 2, 4, 6};
    KRYS_EXPECT_EQUAL("Max Vec4 (2 args)", Max(v4a, v4b), (vec4_t<int> {2, 3, 5, 7}));

    // Vec1 - 3 arguments
    constexpr vec1_t<int> v1c {3};
    KRYS_EXPECT_EQUAL("Max Vec1 (3 args)", Max(v1a, v1b, v1c), (vec1_t<int> {3}));

    // Vec2 - 3 arguments
    constexpr vec2_t<int> v2c {0, 4};
    KRYS_EXPECT_EQUAL("Max Vec2 (3 args)", Max(v2a, v2b, v2c), (vec2_t<int> {2, 4}));

    // Vec3 - 3 arguments
    constexpr vec3_t<int> v3c {0, 6, 3};
    KRYS_EXPECT_EQUAL("Max Vec3 (3 args)", Max(v3a, v3b, v3c), (vec3_t<int> {2, 6, 5}));

    // Vec4 - 3 arguments
    constexpr vec4_t<int> v4c {0, 1, 7, 8};
    KRYS_EXPECT_EQUAL("Max Vec4 (3 args)", Max(v4a, v4b, v4c), (vec4_t<int> {2, 3, 7, 8}));

    // Vec1 - scalar
    constexpr vec1_t<int> v1s {4};
    KRYS_EXPECT_EQUAL("Max Vec1 (scalar)", Max(v1s, 5), (vec1_t<int> {5}));

    // Vec2 - scalar
    constexpr vec2_t<int> v2s {5, 8};
    KRYS_EXPECT_EQUAL("Max Vec2 (scalar)", Max(v2s, 6), (vec2_t<int> {6, 8}));

    // Vec3 - scalar
    constexpr vec3_t<int> v3s {8, 11, 6};
    KRYS_EXPECT_EQUAL("Max Vec3 (scalar)", Max(v3s, 7), (vec3_t<int> {8, 11, 7}));

    // Vec4 - scalar
    constexpr vec4_t<int> v4s {9, 1, 20, 10};
    KRYS_EXPECT_EQUAL("Max Vec4 (scalar)", Max(v4s, 3), (vec4_t<int> {9, 3, 20, 10}));
  }
}
