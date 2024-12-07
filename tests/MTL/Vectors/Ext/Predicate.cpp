#include "MTL/Vectors/Ext/Predicate.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

#pragma region Test Helpers

  constexpr auto IsMoreThan16 = [](int value)
  {
    return value > 16;
  };

  constexpr auto IsLessThan16 = [](int value)
  {
    return value < 16;
  };

#pragma endregion Test Helpers

  static void Test_Vec1_Predicate()
  {
    using vec_t = vec1_t<int>;

    constexpr vec_t vec {1};
    KRYS_EXPECT_TRUE("AnyOf Vec1 (True)", AnyOf(vec, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Vec1 (False)", AnyOf(vec, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Vec1 (True)", AllOf(vec, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Vec1 (False)", AllOf(vec, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Vec1 (True)", NoneOf(vec, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Vec1 (False)", NoneOf(vec, IsLessThan16));
  }

  static void Test_Vec2_Predicate()
  {
    using vec_t = vec2_t<int>;

    constexpr vec_t vec(1, 2);
    KRYS_EXPECT_TRUE("AnyOf Vec2 (True)", AnyOf(vec, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Vec2 (False)", AnyOf(vec, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Vec2 (True)", AllOf(vec, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Vec2 (False)", AllOf(vec, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Vec2 (True)", NoneOf(vec, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Vec2 (False)", NoneOf(vec, IsLessThan16));
  }

  static void Test_Vec3_Predicate()
  {
    using vec_t = vec3_t<int>;

    constexpr vec_t vec(1, 2, 3);
    KRYS_EXPECT_TRUE("AnyOf Vec3 (True)", AnyOf(vec, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Vec3 (False)", AnyOf(vec, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Vec3 (True)", AllOf(vec, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Vec3 (False)", AllOf(vec, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Vec3 (True)", NoneOf(vec, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Vec3 (False)", NoneOf(vec, IsLessThan16));
  }

  static void Test_Vec4_Predicate()
  {
    using vec_t = vec4_t<int>;

    constexpr vec_t vec(1, 2, 3, 4);
    KRYS_EXPECT_TRUE("AnyOf Vec4 (True)", AnyOf(vec, IsLessThan16));
    KRYS_EXPECT_FALSE("AnyOf Vec4 (False)", AnyOf(vec, IsMoreThan16));
    KRYS_EXPECT_TRUE("AllOf Vec4 (True)", AllOf(vec, IsLessThan16));
    KRYS_EXPECT_FALSE("AllOf Vec4 (False)", AllOf(vec, IsMoreThan16));
    KRYS_EXPECT_TRUE("NoneOf Vec4 (True)", NoneOf(vec, IsMoreThan16));
    KRYS_EXPECT_FALSE("NoneOf Vec4 (False)", NoneOf(vec, IsLessThan16));
  }
}
