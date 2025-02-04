#include "MTL/Vectors/Ext/Algorithms.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

#pragma region Test Helpers

  constexpr auto Square = [](int value)
  {
    return value * value;
  };

  constexpr auto AddTwo = [](int left, int right)
  {
    return left + right;
  };

  constexpr auto AddThree = [](int first, int second, int third)
  {
    return first + second + third;
  };

#pragma endregion Test Helpers

  static void Test_Vec1_Algorithms()
  {
    using vec_t = vec1_t<int>;
    constexpr vec_t vec(2);

    constexpr auto forEachSum = [&vec]()
    {
      int total = 0;
      ForEach(vec, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Vec1 ForEach", forEachSum, 2);
    KRYS_EXPECT_EQUAL("Vec1 MapEach", MapEach(vec, Square), vec_t(4));
    KRYS_EXPECT_EQUAL("Vec1 Zip", Zip(vec, vec_t(3), AddTwo), vec_t(5));
    KRYS_EXPECT_EQUAL("Vec1 Zip", Zip(vec, vec_t(3), vec_t(2), AddThree), vec_t(7));
    KRYS_EXPECT_EQUAL("Vec1 Sum(Basic)", Sum(vec), 2);
    KRYS_EXPECT_EQUAL("Vec1 Sum(WithFunc)", Sum(vec, Square), 4);
    KRYS_EXPECT_EQUAL("Vec1 Reverse", Reverse(vec), vec_t(2));
    KRYS_EXPECT_EQUAL("Vec1 MinOf", MinOf(vec), 2);
    KRYS_EXPECT_EQUAL("Vec1 MaxOf", MaxOf(vec), 2);
  }

  static void Test_Vec2_Algorithms()
  {
    using vec_t = vec2_t<int>;
    constexpr vec_t vec(2, 3);

    constexpr auto forEachSum = [&vec]()
    {
      int total = 0;
      ForEach(vec, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Vec2 ForEach", forEachSum, 5);
    KRYS_EXPECT_EQUAL("Vec2 MapEach", MapEach(vec, Square), vec_t(4, 9));
    KRYS_EXPECT_EQUAL("Vec2 Zip", Zip(vec, vec_t(3, 2), AddTwo), vec_t(5, 5));
    KRYS_EXPECT_EQUAL("Vec2 Zip", Zip(vec, vec_t(3, 2), vec_t(2, 3), AddThree), vec_t(7, 8));
    KRYS_EXPECT_EQUAL("Vec2 Sum(Basic)", Sum(vec), 5);
    KRYS_EXPECT_EQUAL("Vec2 Sum(WithFunc)", Sum(vec, Square), 13);
    KRYS_EXPECT_EQUAL("Vec2 Reverse", Reverse(vec), vec_t(3, 2));
    KRYS_EXPECT_EQUAL("Vec2 MinOf", MinOf(vec), 2);
    KRYS_EXPECT_EQUAL("Vec2 MaxOf", MaxOf(vec), 3);
  }

  static void Test_Vec3_Algorithms()
  {
    using vec_t = vec3_t<int>;
    constexpr vec_t vec(2, 3, 4);

    constexpr auto forEachSum = [&vec]()
    {
      int total = 0;
      ForEach(vec, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Vec3 ForEach", forEachSum, 9);
    KRYS_EXPECT_EQUAL("Vec3 MapEach", MapEach(vec, Square), vec_t(4, 9, 16));
    KRYS_EXPECT_EQUAL("Vec3 Zip", Zip(vec, vec_t(3, 2, 5), AddTwo), vec_t(5, 5, 9));
    KRYS_EXPECT_EQUAL("Vec3 Zip", Zip(vec, vec_t(3, 2, 5), vec_t(2, 3, 4), AddThree), vec_t(7, 8, 13));
    KRYS_EXPECT_EQUAL("Vec3 Sum(Basic)", Sum(vec), 9);
    KRYS_EXPECT_EQUAL("Vec3 Sum(WithFunc)", Sum(vec, Square), 29);
    KRYS_EXPECT_EQUAL("Vec3 Reverse", Reverse(vec), vec_t(4, 3, 2));
    KRYS_EXPECT_EQUAL("Vec3 MinOf", MinOf(vec), 2);
    KRYS_EXPECT_EQUAL("Vec3 MaxOf", MaxOf(vec), 4);
  }

  static void Test_Vec4_Algorithms()
  {
    using vec_t = vec4_t<int>;
    constexpr vec_t vec(2, 3, 4, 5);

    constexpr auto forEachSum = [&vec]()
    {
      int total = 0;
      ForEach(vec, [&](int value) { total += value; });
      return total;
    }();

    KRYS_EXPECT_EQUAL("Vec4 ForEach", forEachSum, 14);
    KRYS_EXPECT_EQUAL("Vec4 MapEach", MapEach(vec, Square), vec_t(4, 9, 16, 25));
    KRYS_EXPECT_EQUAL("Vec4 Zip", Zip(vec, vec_t(3, 2, 5, 2), AddTwo), vec_t(5, 5, 9, 7));
    KRYS_EXPECT_EQUAL("Vec4 Zip", Zip(vec, vec_t(3, 2, 5, 2), vec_t(2, 3, 4, 3), AddThree),
                      vec_t(7, 8, 13, 10));
    KRYS_EXPECT_EQUAL("Vec4 Sum(Basic)", Sum(vec), 14);
    KRYS_EXPECT_EQUAL("Vec4 Sum(WithFunc)", Sum(vec, Square), 54);
    KRYS_EXPECT_EQUAL("Vec4 Reverse", Reverse(vec), vec_t(5, 4, 3, 2));
    KRYS_EXPECT_EQUAL("Vec4 MinOf", MinOf(vec), 2);
    KRYS_EXPECT_EQUAL("Vec4 MaxOf", MaxOf(vec), 5);
  }
}
