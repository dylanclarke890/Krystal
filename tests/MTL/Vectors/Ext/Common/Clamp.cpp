#include "MTL/Vectors/Ext/Common/Clamp.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Clamp()
  {
    // Vec1
    constexpr vec1_t<int> v1 {5};
    constexpr vec1_t<int> min1 {1};
    constexpr vec1_t<int> max1 {4};
    KRYS_EXPECT_EQUAL("Clamp Vec1", Clamp(v1, min1, max1), (vec1_t<int> {4}));

    // Vec2
    constexpr vec2_t<int> v2 {5, -1};
    constexpr vec2_t<int> min2 {0, 0};
    constexpr vec2_t<int> max2 {3, 3};
    KRYS_EXPECT_EQUAL("Clamp Vec2", Clamp(v2, min2, max2), (vec2_t<int> {3, 0}));

    // Vec3
    constexpr vec3_t<int> v3 {5, -1, 10};
    constexpr vec3_t<int> min3 {1, 0, 0};
    constexpr vec3_t<int> max3 {4, 2, 8};
    KRYS_EXPECT_EQUAL("Clamp Vec3", Clamp(v3, min3, max3), (vec3_t<int> {4, 0, 8}));

    // Vec4
    constexpr vec4_t<int> v4 {5, -1, 10, 3};
    constexpr vec4_t<int> min4 {1, 0, 0, 2};
    constexpr vec4_t<int> max4 {4, 2, 8, 5};
    KRYS_EXPECT_EQUAL("Clamp Vec4", Clamp(v4, min4, max4), (vec4_t<int> {4, 0, 8, 3}));
  }
}
