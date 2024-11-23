#include "MTL/Vectors/Ext/Common/Min.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Min()
  {
    // Vec1 - 2 arguments
    constexpr vec1_t<int> v1a {1}, v1b {2};
    KRYS_EXPECT_EQUAL("Min Vec1 (2 args)", Min(v1a, v1b), (vec1_t<int> {1}));

    // Vec2 - 2 arguments
    constexpr vec2_t<int> v2a {1, 3}, v2b {2, 2};
    KRYS_EXPECT_EQUAL("Min Vec2 (2 args)", Min(v2a, v2b), (vec2_t<int> {1, 2}));

    // Vec3 - 2 arguments
    constexpr vec3_t<int> v3a {1, 3, 5}, v3b {2, 2, 4};
    KRYS_EXPECT_EQUAL("Min Vec3 (2 args)", Min(v3a, v3b), (vec3_t<int> {1, 2, 4}));

    // Vec4 - 2 arguments
    constexpr vec4_t<int> v4a {1, 3, 5, 7}, v4b {2, 2, 4, 6};
    KRYS_EXPECT_EQUAL("Min Vec4 (2 args)", Min(v4a, v4b), (vec4_t<int> {1, 2, 4, 6}));

    // Vec1 - 3 arguments
    constexpr vec1_t<int> v1c {0};
    KRYS_EXPECT_EQUAL("Min Vec1 (3 args)", Min(v1a, v1b, v1c), (vec1_t<int> {0}));

    // Vec2 - 3 arguments
    constexpr vec2_t<int> v2c {0, 4};
    KRYS_EXPECT_EQUAL("Min Vec2 (3 args)", Min(v2a, v2b, v2c), (vec2_t<int> {0, 2}));

    // Vec3 - 3 arguments
    constexpr vec3_t<int> v3c {0, 1, 3};
    KRYS_EXPECT_EQUAL("Min Vec3 (3 args)", Min(v3a, v3b, v3c), (vec3_t<int> {0, 1, 3}));

    // Vec4 - 3 arguments
    constexpr vec4_t<int> v4c {0, 1, 3, 6};
    KRYS_EXPECT_EQUAL("Min Vec4 (3 args)", Min(v4a, v4b, v4c), (vec4_t<int> {0, 1, 3, 6}));

    // Vec1 - scalar
    constexpr vec1_t<int> v1s {4};
    KRYS_EXPECT_EQUAL("Min Vec1 (scalar)", Min(v1s, 5), (vec1_t<int> {4}));

    // Vec2 - scalar
    constexpr vec2_t<int> v2s {5, 8};
    KRYS_EXPECT_EQUAL("Min Vec2 (scalar)", Min(v2s, 6), (vec2_t<int> {5, 6}));

    // Vec3 - scalar
    constexpr vec3_t<int> v3s {8, 11, 6};
    KRYS_EXPECT_EQUAL("Min Vec3 (scalar)", Min(v3s, 7), (vec3_t<int> {7, 7, 6}));

    // Vec4 - scalar
    constexpr vec4_t<int> v4s {9, 1, 20, 10};
    KRYS_EXPECT_EQUAL("Min Vec4 (scalar)", Min(v4s, 3), (vec4_t<int> {3, 1, 3, 3}));
  }
}
