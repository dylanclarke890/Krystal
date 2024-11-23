#include "MTL/Matrices/Ext/Algorithms.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_ForEach()
  {
    // Mat2x2
    constexpr mat2x2_t<int> v1 {1, 2, 3, 4};
    constexpr auto sum1 = [&]()
    {
      int total = 0;
      ForEach(v1, [&](int value) { total += value; });
      return total;
    }();
    KRYS_EXPECT_EQUAL("ForEach Mat2x2", sum1, 10);

    // Mat3x3
    constexpr mat3x3_t<int> v2 {1, 2, 3, 4, 1, 2, 3, 4, 1};
    constexpr auto sum2 = [&]()
    {
      int total = 0;
      ForEach(v2, [&](int value) { total += value; });
      return total;
    }();
    KRYS_EXPECT_EQUAL("ForEach Mat3x3", sum2, 21);

    // Mat4x4
    constexpr mat4x4_t<int> v3 {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    constexpr auto sum3 = [&]()
    {
      int total = 0;
      ForEach(v3, [&](int value) { total += value; });
      return total;
    }();
    KRYS_EXPECT_EQUAL("ForEach Mat4x4", sum3, 40);
  }

  static void Test_Map()
  {
    constexpr auto square = [](int value)
    {
      return value * value;
    };

    // Mat2x2
    constexpr mat2x2_t<int> v1 {2, 3, 4, 5};
    constexpr mat2x2_t<int> squared1 = MapEach(v1, square);
    KRYS_EXPECT_EQUAL("MapEach Mat2x2", squared1, (mat2x2_t<int> {4, 9, 16, 25}));

    // Mat3x3
    constexpr mat3x3_t<int> v2 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    constexpr mat3x3_t<int> squared2 = MapEach(v2, square);
    KRYS_EXPECT_EQUAL("MapEach Mat3x3", squared2, (mat3x3_t<int> {1, 4, 9, 16, 25, 36, 49, 64, 81}));

    // Mat4x4
    constexpr mat4x4_t<int> v3 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    constexpr mat4x4_t<int> squared3 = MapEach(v3, square);
    KRYS_EXPECT_EQUAL("MapEach Mat4x4", squared3,
                      (mat4x4_t<int> {1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256}));
  }

  static void Test_Zip()
  {
    constexpr auto add = [](int left, int right)
    {
      return left + right;
    };

    // Mat2x2
    constexpr mat2x2_t<int> a1 {1, 2, 3, 4}, b1 {4, 3, 2, 1};
    constexpr mat2x2_t<int> summed1 = Zip(a1, b1, add);
    KRYS_EXPECT_EQUAL("Zip Mat2x2", summed1, (mat2x2_t<int> {5, 5, 5, 5}));

    // Mat3x3
    constexpr mat3x3_t<int> a2 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    constexpr mat3x3_t<int> b2 {9, 8, 7, 6, 5, 4, 3, 2, 1};
    constexpr mat3x3_t<int> summed2 = Zip(a2, b2, add);
    KRYS_EXPECT_EQUAL("Zip Mat3x3", summed2, (mat3x3_t<int> {10, 10, 10, 10, 10, 10, 10, 10, 10}));

    // Mat4x4
    constexpr mat4x4_t<int> a3 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    constexpr mat4x4_t<int> b3 {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    constexpr mat4x4_t<int> summed3 = Zip(a3, b3, add);
    KRYS_EXPECT_EQUAL("Zip Mat4x4", summed3,
                      (mat4x4_t<int> {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17}));
  }

  static void Test_Sum()
  {
    // Mat2x2
    constexpr mat2x2_t<int> v1 {1, 2, 3, 4};
    constexpr int sum1 = Sum(v1);
    KRYS_EXPECT_EQUAL("Sum Mat2x2", sum1, 10);

    // Mat3x3
    constexpr mat3x3_t<int> v2 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    constexpr int sum2 = Sum(v2);
    KRYS_EXPECT_EQUAL("Sum Mat3x3", sum2, 45);

    // Mat4x4
    constexpr mat4x4_t<int> v3 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    constexpr int sum3 = Sum(v3);
    KRYS_EXPECT_EQUAL("Sum Mat4x4", sum3, 136);
  }

  static void Test_SumWithFunc()
  {
    constexpr auto square = [](int value)
    {
      return value * value;
    };

    // Mat2x2
    constexpr mat2x2_t<int> v1 {vec2_t<int> {1, 2}, vec2_t<int> {3, 4}};
    constexpr int sum1 = Sum(v1, square);
    KRYS_EXPECT_EQUAL("SumWithFunc Mat2x2", sum1, 30);

    // Mat3x3
    constexpr mat3x3_t<int> v2 {vec3_t<int> {1, 2, 3}, vec3_t<int> {4, 5, 6}, vec3_t<int> {7, 8, 9}};
    constexpr int sum2 = Sum(v2, square);
    KRYS_EXPECT_EQUAL("SumWithFunc Mat3x3", sum2, 285);

    // Mat4x4
    constexpr mat4x4_t<int> v3 {vec4_t<int> {1, 2, 3, 4}, vec4_t<int> {5, 6, 7, 8},
                                vec4_t<int> {9, 10, 11, 12}, vec4_t<int> {13, 14, 15, 16}};
    constexpr int sum3 = Sum(v3, square);
    KRYS_EXPECT_EQUAL("SumWithFunc Mat4x4", sum3, 1'496);
  }
}
