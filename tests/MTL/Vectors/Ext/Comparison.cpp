#include "MTL/Vectors/Ext/Comparison.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Vec1_Comparison()
  {
    using vec_t = vec1_t<int>;
    using res_t = vec1_t<bool>;

    constexpr vec_t a(1);

    constexpr vec_t b(2);
    KRYS_EXPECT_EQUAL("Comparison (LT) Vec1-Vec1", LessThan(a, b), res_t(true));
    KRYS_EXPECT_EQUAL("Comparison (LE) Vec1-Vec1", LessThanOrEqual(a, b), res_t(true));
    KRYS_EXPECT_EQUAL("Comparison (EQ) Vec1-Vec1", Equal(a, b), res_t(false));
    KRYS_EXPECT_EQUAL("Comparison (NE) Vec1-Vec1", NotEqual(a, b), res_t(true));
    KRYS_EXPECT_EQUAL("Comparison (GT) Vec1-Vec1", GreaterThan(a, b), res_t(false));
    KRYS_EXPECT_EQUAL("Comparison (GE) Vec1-Vec1", GreaterThanOrEqual(a, b), res_t(false));

    constexpr int scalar = 5;
    KRYS_EXPECT_TRUE("Comparison (LT) Vec1-Scalar", LessThan(a, scalar));
    KRYS_EXPECT_TRUE("Comparison (LE) Vec1-Scalar", LessThanOrEqual(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (EQ) Vec1-Scalar", Equal(a, scalar));
    KRYS_EXPECT_TRUE("Comparison (NE) Vec1-Scalar", NotEqual(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (GT) Vec1-Scalar", GreaterThan(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (GE) Vec1-Scalar", GreaterThanOrEqual(a, scalar));
  }

  static void Test_Vec2_Comparison()
  {
    using vec_t = vec2_t<int>;
    using res_t = vec2_t<bool>;

    constexpr vec_t a(1, 2);

    constexpr vec_t b(2, 1);
    KRYS_EXPECT_EQUAL("Comparison (LT) Vec2-Vec2", LessThan(a, b), res_t(true, false));
    KRYS_EXPECT_EQUAL("Comparison (LE) Vec2-Vec2", LessThanOrEqual(a, b), res_t(true, false));
    KRYS_EXPECT_EQUAL("Comparison (EQ) Vec2-Vec2", Equal(a, b), res_t(false, false));
    KRYS_EXPECT_EQUAL("Comparison (NE) Vec2-Vec2", NotEqual(a, b), res_t(true, true));
    KRYS_EXPECT_EQUAL("Comparison (GT) Vec2-Vec2", GreaterThan(a, b), res_t(false, true));
    KRYS_EXPECT_EQUAL("Comparison (GE) Vec2-Vec2", GreaterThanOrEqual(a, b), res_t(false, true));

    constexpr int scalar = 5;
    KRYS_EXPECT_TRUE("Comparison (LT) Vec2-Scalar", LessThan(a, scalar));
    KRYS_EXPECT_TRUE("Comparison (LE) Vec2-Scalar", LessThanOrEqual(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (EQ) Vec2-Scalar", Equal(a, scalar));
    KRYS_EXPECT_TRUE("Comparison (NE) Vec2-Scalar", NotEqual(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (GT) Vec2-Scalar", GreaterThan(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (GE) Vec2-Scalar", GreaterThanOrEqual(a, scalar));
  }

  static void Test_Vec3_Comparison()
  {
    using vec_t = vec3_t<int>;
    using res_t = vec3_t<bool>;

    constexpr vec_t a(1, 2, 3);

    constexpr vec_t b(2, 1, 3);
    KRYS_EXPECT_EQUAL("Comparison (LT) Vec3-Vec3", LessThan(a, b), res_t(true, false, false));
    KRYS_EXPECT_EQUAL("Comparison (LE) Vec3-Vec3", LessThanOrEqual(a, b), res_t(true, false, true));
    KRYS_EXPECT_EQUAL("Comparison (EQ) Vec3-Vec3", Equal(a, b), res_t(false, false, true));
    KRYS_EXPECT_EQUAL("Comparison (NE) Vec3-Vec3", NotEqual(a, b), res_t(true, true, false));
    KRYS_EXPECT_EQUAL("Comparison (GT) Vec3-Vec3", GreaterThan(a, b), res_t(false, true, false));
    KRYS_EXPECT_EQUAL("Comparison (GE) Vec3-Vec3", GreaterThanOrEqual(a, b), res_t(false, true, true));

    constexpr int scalar = 5;
    KRYS_EXPECT_TRUE("Comparison (LT) Vec3-Scalar", LessThan(a, scalar));
    KRYS_EXPECT_TRUE("Comparison (LE) Vec3-Scalar", LessThanOrEqual(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (EQ) Vec3-Scalar", Equal(a, scalar));
    KRYS_EXPECT_TRUE("Comparison (NE) Vec3-Scalar", NotEqual(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (GT) Vec3-Scalar", GreaterThan(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (GE) Vec3-Scalar", GreaterThanOrEqual(a, scalar));
  }

  static void Test_Vec4_Comparison()
  {
    using vec_t = vec4_t<int>;
    using res_t = vec4_t<bool>;

    constexpr vec_t a(1, 2, 3, 4);

    constexpr vec_t b(2, 1, 3, 4);
    KRYS_EXPECT_EQUAL("Comparison (LT) Vec3-Vec3", LessThan(a, b), res_t(true, false, false, false));
    KRYS_EXPECT_EQUAL("Comparison (LE) Vec3-Vec3", LessThanOrEqual(a, b), res_t(true, false, true, true));
    KRYS_EXPECT_EQUAL("Comparison (EQ) Vec3-Vec3", Equal(a, b), res_t(false, false, true, true));
    KRYS_EXPECT_EQUAL("Comparison (NE) Vec3-Vec3", NotEqual(a, b), res_t(true, true, false, false));
    KRYS_EXPECT_EQUAL("Comparison (GT) Vec3-Vec3", GreaterThan(a, b), res_t(false, true, false, false));
    KRYS_EXPECT_EQUAL("Comparison (GE) Vec3-Vec3", GreaterThanOrEqual(a, b), res_t(false, true, true, true));

    constexpr int scalar = 5;
    KRYS_EXPECT_TRUE("Comparison (LT) Vec3-Scalar", LessThan(a, scalar));
    KRYS_EXPECT_TRUE("Comparison (LE) Vec3-Scalar", LessThanOrEqual(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (EQ) Vec3-Scalar", Equal(a, scalar));
    KRYS_EXPECT_TRUE("Comparison (NE) Vec3-Scalar", NotEqual(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (GT) Vec3-Scalar", GreaterThan(a, scalar));
    KRYS_EXPECT_FALSE("Comparison (GE) Vec3-Scalar", GreaterThanOrEqual(a, scalar));
  }
}
