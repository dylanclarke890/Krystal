#include "MTL/Vectors/Ext/Algorithms.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_ForEach()
  {
    // Vec1
    constexpr vec1_t<int> v1 {1};
    constexpr auto sum1 = [&]()
    {
      int total = 0;
      ForEach(v1, [&](int value) { total += value; });
      return total;
    }();
    KRYS_EXPECT_EQUAL("ForEach Vec1", sum1, 1);

    // Vec2
    constexpr vec2_t<int> v2 {1, 2};
    constexpr auto sum2 = [&]()
    {
      int total = 0;
      ForEach(v2, [&](int value) { total += value; });
      return total;
    }();
    KRYS_EXPECT_EQUAL("ForEach Vec2", sum2, 3);

    // Vec3
    constexpr vec3_t<int> v3 {1, 2, 3};
    constexpr auto sum3 = [&]()
    {
      int total = 0;
      ForEach(v3, [&](int value) { total += value; });
      return total;
    }();
    KRYS_EXPECT_EQUAL("ForEach Vec3", sum3, 6);

    // Vec4
    constexpr vec4_t<int> v4 {1, 2, 3, 4};
    constexpr auto sum4 = [&]()
    {
      int total = 0;
      ForEach(v4, [&](int value) { total += value; });
      return total;
    }();
    KRYS_EXPECT_EQUAL("ForEach Vec4", sum4, 10);
  }

  static void Test_Map()
  {
    constexpr auto square = [](int value)
    {
      return value * value;
    };

    // Vec1
    constexpr vec1_t<int> v1 {2};
    constexpr vec1_t<int> squared1 = MapEach(v1, square);
    KRYS_EXPECT_EQUAL("MapEach Vec1", squared1, (vec1_t<int> {4}));

    // Vec2
    constexpr vec2_t<int> v2 {1, 2};
    constexpr vec2_t<int> squared2 = MapEach(v2, square);
    KRYS_EXPECT_EQUAL("MapEach Vec2", squared2, (vec2_t<int> {1, 4}));

    // Vec3
    constexpr vec3_t<int> v3 {1, 2, 3};
    constexpr vec3_t<int> squared3 = MapEach(v3, square);
    KRYS_EXPECT_EQUAL("MapEach Vec3", squared3, (vec3_t<int> {1, 4, 9}));

    // Vec4
    constexpr vec4_t<int> v4 {1, 2, 3, 4};
    constexpr vec4_t<int> squared4 = MapEach(v4, square);
    KRYS_EXPECT_EQUAL("MapEach Vec4", squared4, (vec4_t<int> {1, 4, 9, 16}));
  }

  static void Test_Zip()
  {
    constexpr auto add = [](int left, int right)
    {
      return left + right;
    };

    // Vec1
    constexpr vec1_t<int> a1 {1}, b1 {2};
    constexpr vec1_t<int> summed1 = Zip(a1, b1, add);
    KRYS_EXPECT_EQUAL("Zip Vec1", summed1, (vec1_t<int> {3}));

    // Vec2
    constexpr vec2_t<int> a2 {1, 2}, b2 {2, 3};
    constexpr vec2_t<int> summed2 = Zip(a2, b2, add);
    KRYS_EXPECT_EQUAL("Zip Vec2", summed2, (vec2_t<int> {3, 5}));

    // Vec3
    constexpr vec3_t<int> a3 {1, 2, 3}, b3 {2, 3, 4};
    constexpr vec3_t<int> summed3 = Zip(a3, b3, add);
    KRYS_EXPECT_EQUAL("Zip Vec3", summed3, (vec3_t<int> {3, 5, 7}));

    // Vec4
    constexpr vec4_t<int> a4 {1, 2, 3, 4}, b4 {4, 3, 2, 1};
    constexpr vec4_t<int> summed4 = Zip(a4, b4, add);
    KRYS_EXPECT_EQUAL("Zip Vec4", summed4, (vec4_t<int> {5, 5, 5, 5}));
  }

  static void Test_Sum()
  {
    // Vec1
    constexpr vec1_t<int> v1 {1};
    constexpr int sum1 = Sum(v1);
    KRYS_EXPECT_EQUAL("Sum Vec1", sum1, 1);

    // Vec2
    constexpr vec2_t<int> v2 {1, 2};
    constexpr int sum2 = Sum(v2);
    KRYS_EXPECT_EQUAL("Sum Vec2", sum2, 3);

    // Vec3
    constexpr vec3_t<int> v3 {1, 2, 3};
    constexpr int sum3 = Sum(v3);
    KRYS_EXPECT_EQUAL("Sum Vec3", sum3, 6);

    // Vec4
    constexpr vec4_t<int> v4 {1, 2, 3, 4};
    constexpr int sum4 = Sum(v4);
    KRYS_EXPECT_EQUAL("Sum Vec4", sum4, 10);
  }

  static void Test_SumWithFunc()
  {
    constexpr auto square = [](int value)
    {
      return value * value;
    };

    // Vec1
    constexpr vec1_t<int> v1 {2};
    constexpr int sum1 = Sum(v1, square);
    KRYS_EXPECT_EQUAL("SumWithFunc Vec1", sum1, 4);

    // Vec2
    constexpr vec2_t<int> v2 {1, 2};
    constexpr int sum2 = Sum(v2, square);
    KRYS_EXPECT_EQUAL("SumWithFunc Vec2", sum2, 5);

    // Vec3
    constexpr vec3_t<int> v3 {1, 2, 3};
    constexpr int sum3 = Sum(v3, square);
    KRYS_EXPECT_EQUAL("SumWithFunc Vec3", sum3, 14);

    // Vec4
    constexpr vec4_t<int> v4 {1, 2, 3, 4};
    constexpr int sum4 = Sum(v4, square);
    KRYS_EXPECT_EQUAL("SumWithFunc Vec4", sum4, 30);
  }
}
