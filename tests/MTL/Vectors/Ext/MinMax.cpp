#include "MTL/Vectors/Ext/MinMax.hpp"
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

  static void Test_FMax()
  {
    // Vec1 - 2 arguments
    constexpr vec1_t<float> v1a {1.0f}, v1b {2.0f};
    KRYS_EXPECT_EQUAL("FMax Vec1 (2 args)", FMax(v1a, v1b), (vec1_t<float> {2.0f}));

    // Vec2 - 2 arguments
    constexpr vec2_t<float> v2a {1.0f, 3.0f}, v2b {2.0f, 2.0f};
    KRYS_EXPECT_EQUAL("FMax Vec2 (2 args)", FMax(v2a, v2b), (vec2_t<float> {2.0f, 3.0f}));

    // Vec3 - 2 arguments
    constexpr vec3_t<float> v3a {1.0f, 3.0f, 5.0f}, v3b {2.0f, 2.0f, 4.0f};
    KRYS_EXPECT_EQUAL("FMax Vec3 (2 args)", FMax(v3a, v3b), (vec3_t<float> {2.0f, 3.0f, 5.0f}));

    // Vec4 - 2 arguments
    constexpr vec4_t<float> v4a {1.0f, 3.0f, 5.0f, 7.0f}, v4b {2.0f, 2.0f, 4.0f, 6.0f};
    KRYS_EXPECT_EQUAL("FMax Vec4 (2 args)", FMax(v4a, v4b), (vec4_t<float> {2.0f, 3.0f, 5.0f, 7.0f}));

    // Vec1 - 3 arguments
    constexpr vec1_t<float> v1c {3.0f};
    KRYS_EXPECT_EQUAL("FMax Vec1 (3 args)", FMax(v1a, v1b, v1c), (vec1_t<float> {3.0f}));

    // Vec2 - 3 arguments
    constexpr vec2_t<float> v2c {0.0f, 4.0f};
    KRYS_EXPECT_EQUAL("FMax Vec2 (3 args)", FMax(v2a, v2b, v2c), (vec2_t<float> {2.0f, 4.0f}));

    // Vec3 - 3 arguments
    constexpr vec3_t<float> v3c {0.0f, 6.0f, 3.0f};
    KRYS_EXPECT_EQUAL("FMax Vec3 (3 args)", FMax(v3a, v3b, v3c), (vec3_t<float> {2.0f, 6.0f, 5.0f}));

    // Vec4 - 3 arguments
    constexpr vec4_t<float> v4c {0.0f, 1.0f, 7.0f, 8.0f};
    KRYS_EXPECT_EQUAL("FMax Vec4 (3 args)", FMax(v4a, v4b, v4c), (vec4_t<float> {2.0f, 3.0f, 7.0f, 8.0f}));

    // Vec1 - scalar
    constexpr vec1_t<float> v1s {4.0f};
    KRYS_EXPECT_EQUAL("FMax Vec1 (scalar)", FMax(v1s, 5.0f), (vec1_t<float> {5.0f}));

    // Vec2 - scalar
    constexpr vec2_t<float> v2s {5.0f, 8.0f};
    KRYS_EXPECT_EQUAL("FMax Vec2 (scalar)", FMax(v2s, 6.0f), (vec2_t<float> {6.0f, 8.0f}));

    // Vec3 - scalar
    constexpr vec3_t<float> v3s {8.0f, 11.0f, 6.0f};
    KRYS_EXPECT_EQUAL("FMax Vec3 (scalar)", FMax(v3s, 3.0f), (vec3_t<float> {8.0f, 11.0f, 6.0f}));

    // Vec4 - scalar
    constexpr vec4_t<float> v4s {9.0f, 1.0f, 20.0f, 10.0f};
    KRYS_EXPECT_EQUAL("FMax Vec4 (scalar)", FMax(v4s, 3.0f), (vec4_t<float> {9.0f, 3.0f, 20.0f, 10.0f}));
  }
}
