#include "MTL/Matrices/Ext/OuterProduct.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat2x3.hpp"
#include "MTL/Matrices/Mat2x4.hpp"
#include "MTL/Matrices/Mat3x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x2.hpp"
#include "MTL/Matrices/Mat4x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  static void Test_OuterProduct_Mat2x2()
  {
    using vec_a = vec2_t<int>;
    using vec_b = vec2_t<int>;
    using mat_t = mat2x2_t<int>;

    constexpr vec_a a(1, 2);
    constexpr vec_b b(3, 4);
    constexpr auto result = MTL::OuterProduct(a, b);

    KRYS_EXPECT_EQUAL("OuterProduct Mat2x2", result, mat_t(3, 6, 4, 8));
  }

  static void Test_OuterProduct_Mat2x3()
  {
    using vec_a = vec2_t<int>;
    using vec_b = vec3_t<int>;
    using mat_t = mat2x3_t<int>;

    constexpr vec_a a(1, 2);
    constexpr vec_b b(3, 4, 5);
    constexpr auto result = MTL::OuterProduct(a, b);

    KRYS_EXPECT_EQUAL("OuterProduct Mat2x3", result, mat_t(3, 6, 4, 8, 5, 10));
  }

  static void Test_OuterProduct_Mat2x4()
  {
    using vec_a = vec2_t<int>;
    using vec_b = vec4_t<int>;
    using mat_t = mat2x4_t<int>;

    constexpr vec_a a(1, 2);
    constexpr vec_b b(3, 4, 5, 6);
    constexpr auto result = MTL::OuterProduct(a, b);

    KRYS_EXPECT_EQUAL("OuterProduct Mat2x4", result, mat_t(3, 6, 4, 8, 5, 10, 6, 12));
  }

  static void Test_OuterProduct_Mat3x2()
  {
    using vec_a = vec3_t<int>;
    using vec_b = vec2_t<int>;
    using mat_t = mat3x2_t<int>;

    constexpr vec_a a(1, 2, 3);
    constexpr vec_b b(4, 5);
    constexpr auto result = MTL::OuterProduct(a, b);

    KRYS_EXPECT_EQUAL("OuterProduct Mat3x2", result, mat_t(4, 8, 12, 5, 10, 15));
  }

  static void Test_OuterProduct_Mat3x3()
  {
    using vec_a = vec3_t<int>;
    using vec_b = vec3_t<int>;
    using mat_t = mat3x3_t<int>;

    constexpr vec_a a(1, 2, 3);
    constexpr vec_b b(4, 5, 6);
    constexpr auto result = MTL::OuterProduct(a, b);

    KRYS_EXPECT_EQUAL("OuterProduct Mat3x3", result, mat_t(4, 8, 12, 5, 10, 15, 6, 12, 18));
  }

  static void Test_OuterProduct_Mat3x4()
  {
    using vec_a = vec3_t<int>;
    using vec_b = vec4_t<int>;
    using mat_t = mat3x4_t<int>;

    constexpr vec_a a(1, 2, 3);
    constexpr vec_b b(4, 5, 6, 7);
    constexpr auto result = MTL::OuterProduct(a, b);

    KRYS_EXPECT_EQUAL("OuterProduct Mat3x4", result, mat_t(4, 8, 12, 5, 10, 15, 6, 12, 18, 7, 14, 21));
  }

  static void Test_OuterProduct_Mat4x2()
  {
    using vec_a = vec4_t<int>;
    using vec_b = vec2_t<int>;
    using mat_t = mat4x2_t<int>;

    constexpr vec_a a(1, 2, 3, 4);
    constexpr vec_b b(5, 6);
    constexpr auto result = MTL::OuterProduct(a, b);

    KRYS_EXPECT_EQUAL("OuterProduct Mat4x2", result, mat_t(5, 10, 15, 20, 6, 12, 18, 24));
  }

  static void Test_OuterProduct_Mat4x3()
  {
    using vec_a = vec4_t<int>;
    using vec_b = vec3_t<int>;
    using mat_t = mat4x3_t<int>;

    constexpr vec_a a(1, 2, 3, 4);
    constexpr vec_b b(5, 6, 7);
    constexpr auto result = MTL::OuterProduct(a, b);

    KRYS_EXPECT_EQUAL("OuterProduct Mat4x3", result, mat_t(5, 10, 15, 20, 6, 12, 18, 24, 7, 14, 21, 28));
  }

  static void Test_OuterProduct_Mat4x4()
  {
    using vec_a = vec4_t<int>;
    using vec_b = vec4_t<int>;
    using mat_t = mat4x4_t<int>;

    constexpr vec_a a(1, 2, 3, 4);
    constexpr vec_b b(5, 6, 7, 8);
    constexpr auto result = MTL::OuterProduct(a, b);

    KRYS_EXPECT_EQUAL("OuterProduct Mat4x4", result,
                      mat_t(5, 10, 15, 20, 6, 12, 18, 24, 7, 14, 21, 28, 8, 16, 24, 32));
  }
}