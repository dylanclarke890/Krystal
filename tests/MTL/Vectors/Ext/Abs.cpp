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

  static void Test_Vec1_Abs()
  {
    using vec_t = Vec1;
    constexpr vec_t vec {-1};
    KRYS_EXPECT_EQUAL("Abs Vec1", Abs(vec), vec_t(1));
  }

  static void Test_Vec2_Abs()
  {
    using vec_t = Vec2;
    constexpr vec_t vec {-1, -2};
    KRYS_EXPECT_EQUAL("Abs Vec2", Abs(vec), vec_t(1, 2));
  }

  static void Test_Vec3_Abs()
  {
    using vec_t = Vec3;
    constexpr vec_t vec {-1, -2, -3};
    KRYS_EXPECT_EQUAL("Abs Vec3", Abs(vec), vec_t(1, 2, 3));
  }

  static void Test_Vec4_Abs()
  {
    using vec_t = Vec4;
    constexpr vec_t vec {-1, -2, -3, -4};
    KRYS_EXPECT_EQUAL("Abs Vec4", Abs(vec), vec_t(1, 2, 3, 4));
  }
}