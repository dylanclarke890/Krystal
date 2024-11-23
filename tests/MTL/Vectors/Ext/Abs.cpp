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
    constexpr vec1_t<int> v1 {-1};
    KRYS_EXPECT_EQUAL("Abs Vec1", Abs(v1), (vec1_t<int> {1}));

    // Vec2
    constexpr vec2_t<int> v2 {-1, -2};
    KRYS_EXPECT_EQUAL("Abs Vec2", Abs(v2), (vec2_t<int> {1, 2}));

    // Vec3
    constexpr vec3_t<int> v3 {-1, -2, -3};
    KRYS_EXPECT_EQUAL("Abs Vec3", Abs(v3), (vec3_t<int> {1, 2, 3}));

    // Vec4
    constexpr vec4_t<int> v4 {-1, -2, -3, -4};
    KRYS_EXPECT_EQUAL("Abs Vec4", Abs(v4), (vec4_t<int> {1, 2, 3, 4}));
  }
}