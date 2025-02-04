#include "MTL/Vectors/Ext/Rounding.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Vec1_Rounding()
  {
    using vec_t = Vec1;

    constexpr vec_t vec(1.1f);

    KRYS_EXPECT_EQUAL("Ceil Vec1", Ceil(vec), vec_t(2));
    KRYS_EXPECT_EQUAL("Floor Vec1", Floor(vec), vec_t(1));
    KRYS_EXPECT_EQUAL("Round Vec1", Round(vec), vec_t(1));
    KRYS_EXPECT_EQUAL("Trunc Vec1", Trunc(vec), vec_t(1));
  }

  static void Test_Vec2_Rounding()
  {
    using vec_t = Vec2;

    constexpr vec_t vec(1.1f, 2.8f);

    KRYS_EXPECT_EQUAL("Ceil Vec1", Ceil(vec), vec_t(2, 3));
    KRYS_EXPECT_EQUAL("Floor Vec1", Floor(vec), vec_t(1, 2));
    KRYS_EXPECT_EQUAL("Round Vec1", Round(vec), vec_t(1, 3));
    KRYS_EXPECT_EQUAL("Trunc Vec1", Trunc(vec), vec_t(1, 2));
  }

  static void Test_Vec3_Rounding()
  {
    using vec_t = Vec3;

    constexpr vec_t vec(1.1f, 2.8f, -1.1f);

    KRYS_EXPECT_EQUAL("Ceil Vec1", Ceil(vec), vec_t(2, 3, -1));
    KRYS_EXPECT_EQUAL("Floor Vec1", Floor(vec), vec_t(1, 2, -2));
    KRYS_EXPECT_EQUAL("Round Vec1", Round(vec), vec_t(1, 3, -1));
    KRYS_EXPECT_EQUAL("Trunc Vec1", Trunc(vec), vec_t(1, 2, -1));
  }

  static void Test_Vec4_Rounding()
  {
    using vec_t = Vec4;

    constexpr vec_t vec(1.1f, 2.8f, -1.1f, -2.8f);

    KRYS_EXPECT_EQUAL("Ceil Vec1", Ceil(vec), vec_t(2, 3, -1, -2));
    KRYS_EXPECT_EQUAL("Floor Vec1", Floor(vec), vec_t(1, 2, -2, -3));
    KRYS_EXPECT_EQUAL("Round Vec1", Round(vec), vec_t(1, 3, -1, -3));
    KRYS_EXPECT_EQUAL("Trunc Vec1", Trunc(vec), vec_t(1, 2, -1, -2));
  }
}
