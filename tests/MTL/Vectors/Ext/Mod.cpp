#include "MTL/Vectors/Ext/Mod.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Mod()
  {
    // Vec1
    constexpr vec1_t<int> v1 {5};
    constexpr vec1_t<int> mod1 {3};
    KRYS_EXPECT_EQUAL("Mod Vec1", Mod(v1, mod1), (vec1_t<int> {2}));

    // Vec2
    constexpr vec2_t<int> v2 {5, 8};
    constexpr vec2_t<int> mod2 {3, 5};
    KRYS_EXPECT_EQUAL("Mod Vec2", Mod(v2, mod2), (vec2_t<int> {2, 3}));

    // Vec3
    constexpr vec3_t<int> v3 {5, 8, 14};
    constexpr vec3_t<int> mod3 {3, 5, 4};
    KRYS_EXPECT_EQUAL("Mod Vec3", Mod(v3, mod3), (vec3_t<int> {2, 3, 2}));

    // Vec4
    constexpr vec4_t<int> v4 {5, 8, 14, 20};
    constexpr vec4_t<int> mod4 {3, 5, 4, 6};
    KRYS_EXPECT_EQUAL("Mod Vec4", Mod(v4, mod4), (vec4_t<int> {2, 3, 2, 2}));
  }
}
