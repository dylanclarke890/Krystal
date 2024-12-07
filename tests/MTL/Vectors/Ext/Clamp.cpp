#include "MTL/Vectors/Ext/Clamp.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Vec1_Clamp()
  {
    using vec_t = vec1_t<int>;
    constexpr vec_t vec(6);

    KRYS_EXPECT_EQUAL("Clamp Vec1-Vec1", Clamp(vec, vec_t(1), vec_t(5)), vec_t(5));
    KRYS_EXPECT_EQUAL("Clamp Vec1-Scalar", Clamp(vec, 4, 7), vec_t(6));
  }

  static void Test_Vec2_Clamp()
  {
    using vec_t = vec2_t<int>;
    constexpr vec_t vec(6, 3);

    KRYS_EXPECT_EQUAL("Clamp Vec2-Vec2", Clamp(vec, vec_t(1, 4), vec_t(5, 5)), vec_t(5, 4));
    KRYS_EXPECT_EQUAL("Clamp Vec2-Scalar", Clamp(vec, 4, 7), vec_t(6, 4));
  }

  static void Test_Vec3_Clamp()
  {
    using vec_t = vec3_t<int>;
    constexpr vec_t vec {5, -1, 10};

    KRYS_EXPECT_EQUAL("Clamp Vec3-Vec3", Clamp(vec, vec_t(1, 0, 0), vec_t(4, 2, 8)), vec_t(4, 0, 8));
    KRYS_EXPECT_EQUAL("Clamp Vec3-Scalar", Clamp(vec, 1, 9), vec_t(5, 1, 9));
  }

  static void Test_Vec4_Clamp()
  {
    using vec_t = vec4_t<int>;
    constexpr vec_t vec {5, -1, 10, 11};

    KRYS_EXPECT_EQUAL("Clamp Vec3-Vec3", Clamp(vec, vec_t(1, 0, 0, 0), vec_t(4, 2, 8, 1)), vec_t(4, 0, 8, 1));
    KRYS_EXPECT_EQUAL("Clamp Vec3-Scalar", Clamp(vec, 1, 9), vec_t(5, 1, 9, 9));
  }
}
