#include "MTL/Matrices/Ext/Predicate.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_AnyOf()
  {
    // Mat2x2
    constexpr mat2x2_t<int> m1 {1, -1, 0, 5};
    KRYS_EXPECT_TRUE("AnyOf Mat2x2 (True)", AnyOf(m1, [](int value) { return value < 0; }));
    KRYS_EXPECT_FALSE("AnyOf Mat2x2 (False)", AnyOf(m1, [](int value) { return value > 10; }));

    // Mat3x3
    constexpr mat3x3_t<int> m2 {1, 2, 3, 4, -5, 6, 7, 8, 9};
    KRYS_EXPECT_TRUE("AnyOf Mat3x3 (True)", AnyOf(m2, [](int value) { return value < 0; }));
    KRYS_EXPECT_FALSE("AnyOf Mat3x3 (False)", AnyOf(m2, [](int value) { return value > 10; }));

    // Mat4x4
    constexpr mat4x4_t<int> m3 {1, 2, -3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    KRYS_EXPECT_TRUE("AnyOf Mat4x4 (True)", AnyOf(m3, [](int value) { return value < 0; }));
    KRYS_EXPECT_FALSE("AnyOf Mat4x4 (False)", AnyOf(m3, [](int value) { return value > 20; }));
  }

  static void Test_AllOf()
  {
    // Mat2x2
    constexpr mat2x2_t<int> m1 {1, 2, 3, 4};
    KRYS_EXPECT_TRUE("AllOf Mat2x2 (True)", AllOf(m1, [](int value) { return value > 0; }));
    KRYS_EXPECT_FALSE("AllOf Mat2x2 (False)", AllOf(m1, [](int value) { return value < 3; }));

    // Mat3x3
    constexpr mat3x3_t<int> m2 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    KRYS_EXPECT_TRUE("AllOf Mat3x3 (True)", AllOf(m2, [](int value) { return value > 0; }));
    KRYS_EXPECT_FALSE("AllOf Mat3x3 (False)", AllOf(m2, [](int value) { return value <= 5; }));

    // Mat4x4
    constexpr mat4x4_t<int> m3 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    KRYS_EXPECT_TRUE("AllOf Mat4x4 (True)", AllOf(m3, [](int value) { return value > 0; }));
    KRYS_EXPECT_FALSE("AllOf Mat4x4 (False)", AllOf(m3, [](int value) { return value < 10; }));
  }

  static void Test_NoneOf()
  {
    // Mat2x2
    constexpr mat2x2_t<int> m1 {1, 2, 3, 4};
    KRYS_EXPECT_TRUE("NoneOf Mat2x2 (True)", NoneOf(m1, [](int value) { return value < 0; }));
    KRYS_EXPECT_FALSE("NoneOf Mat2x2 (False)", NoneOf(m1, [](int value) { return value > 2; }));

    // Mat3x3
    constexpr mat3x3_t<int> m2 {1, 2, 3, 4, 5, 6, 7, 8, 9};
    KRYS_EXPECT_TRUE("NoneOf Mat3x3 (True)", NoneOf(m2, [](int value) { return value < 0; }));
    KRYS_EXPECT_FALSE("NoneOf Mat3x3 (False)", NoneOf(m2, [](int value) { return value == 5; }));

    // Mat4x4
    constexpr mat4x4_t<int> m3 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    KRYS_EXPECT_TRUE("NoneOf Mat4x4 (True)", NoneOf(m3, [](int value) { return value < 0; }));
    KRYS_EXPECT_FALSE("NoneOf Mat4x4 (False)", NoneOf(m3, [](int value) { return value == 8; }));
  }
}
