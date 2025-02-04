#include "MTL/Vectors/Ext/Mod.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Vec1_Mod()
  {
    using vec_t = vec1_t<int>;
    constexpr vec_t vec(5);

    KRYS_EXPECT_EQUAL("Mod Vec1", Mod(vec, vec_t(3)), vec_t(2));
  }

  static void Test_Vec2_Mod()
  {
    using vec_t = vec2_t<int>;
    constexpr vec_t vec(5, 3);

    KRYS_EXPECT_EQUAL("Mod Vec2", Mod(vec, vec_t(3, 2)), vec_t(2, 1));
  }

  static void Test_Vec3_Mod()
  {
    using vec_t = vec3_t<int>;
    constexpr vec_t vec(5, 3, 8);

    KRYS_EXPECT_EQUAL("Mod Vec3", Mod(vec, vec_t(3, 2, 4)), vec_t(2, 1, 0));
  }

  static void Test_Vec4_Mod()
  {
    using vec_t = vec4_t<int>;
    constexpr vec_t vec(5, 3, 8, 7);

    KRYS_EXPECT_EQUAL("Mod Vec4", Mod(vec, vec_t(3, 2, 4, 3)), vec_t(2, 1, 0, 1));
  }
}
