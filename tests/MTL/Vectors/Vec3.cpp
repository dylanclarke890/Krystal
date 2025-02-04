#include "MTL/Vectors/Vec3.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using vec_t = vec3_t<float>;

  static void Test_Vec3_Constructors()
  {
    constexpr vec_t empty(0);
    KRYS_EXPECT_EQUAL("Vec3 Default Constructor", empty, vec_t(0, 0, 0));

    constexpr vec_t scalar(1);
    KRYS_EXPECT_EQUAL("Vec3 Scalar Constructor", scalar, vec_t(1, 1, 1));

    constexpr vec_t copy(scalar);
    KRYS_EXPECT_EQUAL("Vec3 Copy Constructor", copy, scalar);

    constexpr vec_t move_src(scalar);
    constexpr vec_t move_dst(std::move(move_src));
    KRYS_EXPECT_EQUAL("Vec3 Move Constructor", move_dst, scalar);
  }

  static void Test_Vec3_Assignment()
  {
    constexpr auto TestCopy = []()
    {
      vec_t a {};
      vec_t b {5, 3, 2};

      a = b;
      return a == vec_t(5, 3, 2);
    };

    constexpr auto TestMove = []()
    {
      vec_t a {};
      vec_t b {5, 3, 2};

      a = std::move(b);
      return a == vec_t(5, 3, 2);
    };

    constexpr auto TestIndexAssignment = []()
    {
      vec_t a {};

      a[0] = 5.0f;
      a[1] = 3.0f;
      a[2] = 2.0f;
      return a == vec_t(5, 3, 2);
    };

    constexpr auto TestGetAssignment = []()
    {
      vec_t a {};

      a.Get<0>() = 5.0f;
      a.Get<1>() = 3.0f;
      a.Get<2>() = 2.0f;
      return a == vec_t(5, 3, 2);
    };

    KRYS_EXPECT_TRUE("Vec3 Copy Assignment", TestCopy());
    KRYS_EXPECT_TRUE("Vec3 Move Assignment", TestMove());
    KRYS_EXPECT_TRUE("Vec3 Index Assignment", TestIndexAssignment());
    KRYS_EXPECT_TRUE("Vec3 Get Assignment", TestGetAssignment());
  }

  static void Test_Vec3_Equality()
  {
    constexpr vec_t vec(1, 0, 3);
    constexpr vec_t unequal(0, 1, 2);

    KRYS_EXPECT_TRUE("Vec3 Equality Comparison - Equal", vec == vec);
    KRYS_EXPECT_FALSE("Vec3 Equality Comparison - Not Equal", vec == unequal);
    KRYS_EXPECT_TRUE("Vec3 Inequality Comparison - Not Equal", vec != unequal);
  }

  static void Test_Vec3_ElementAccess()
  {
    constexpr vec_t vec(1, 2, 3);
    KRYS_EXPECT_EQUAL("Vec3 GetLength()", vec.GetLength(), 3);

    KRYS_EXPECT_EQUAL("Vec3 Element Access [0]", vec[0], 1);
    KRYS_EXPECT_EQUAL("Vec3 Element Access [1]", vec[1], 2);
    KRYS_EXPECT_EQUAL("Vec3 Element Access [2]", vec[2], 3);

    KRYS_EXPECT_EQUAL("Vec3 Element Access Get<0>()", vec.Get<0>(), 1);
    KRYS_EXPECT_EQUAL("Vec3 Element Access Get<1>()", vec.Get<1>(), 2);
    KRYS_EXPECT_EQUAL("Vec3 Element Access Get<2>()", vec.Get<2>(), 3);
  }

  static void Test_Vec3_Unary()
  {
    KRYS_EXPECT_EQUAL("Vec3 Unary Negation", -vec_t(1, 3, 5), vec_t(-1, -3, -5));
    KRYS_EXPECT_EQUAL("Vec3 Unary Plus", +vec_t(-1, 3, -5), vec_t(-1, 3, -5));
  }

  static void Test_Vec3_Addition()
  {
    constexpr vec_t vec(1, 2, 3);
    KRYS_EXPECT_EQUAL("Vec3 Vector Addition", vec + vec_t(9, 8, 7), vec_t(10));
    KRYS_EXPECT_EQUAL("Vec3 Scalar Addition", vec + 9.0f, vec_t(10, 11, 12));
  }

  static void Test_Vec3_Subtraction()
  {
    constexpr vec_t vec(1, 2, 3);
    KRYS_EXPECT_EQUAL("Vec3 Vector Subtraction", vec - vec_t(9, 10, 11), vec_t(-8, -8, -8));
    KRYS_EXPECT_EQUAL("Vec3 Scalar Subtraction", vec - 9.0f, vec_t(-8, -7, -6));
  }

  static void Test_Vec3_Multiplication()
  {
    constexpr vec_t vec(3, 4, 5);
    KRYS_EXPECT_EQUAL("Vec3 Vector Multiplication", vec * vec_t(5, 2, 4), vec_t(15, 8, 20));
    KRYS_EXPECT_EQUAL("Vec3 Scalar Multiplication", vec * 5.0f, vec_t(15, 20, 25));
  }

  static void Test_Vec3_Division()
  {
    constexpr vec_t vec(2, 4, 6);
    KRYS_EXPECT_EQUAL("Vec3 Vector Division", vec / vec_t(2, 4, 6), vec_t(1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec3 Scalar Division", vec / 4.0f, vec_t(0.5f, 1, 1.5f));
  }

  static void Test_Vec3_Bitwise_ShiftLeft()
  {
    using ivec = vec3_t<int>;

    KRYS_EXPECT_EQUAL("Vec3 << - Scalar", ivec(1) << 1, ivec(2));
    constexpr ivec vec = ([]() {
        ivec vec(1);
        vec <<= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec3 <<= - Scalar", vec, ivec(4));
  }

  static void Test_Vec3_Bitwise_ShiftRight()
  {
    using ivec = vec3_t<int>;

    KRYS_EXPECT_EQUAL("Vec3 >> - Scalar", ivec(2) >> 1, ivec(1));
    constexpr ivec vec = ([]() {
        ivec vec(4);
        vec >>= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec3 >>= - Scalar", vec, ivec(1));
  }

  static void Test_Vec3_Bitwise_Or()
  {
    using ivec = vec3_t<int>;

    KRYS_EXPECT_EQUAL("Vec3 | - Scalar", ivec(2) | 1, ivec(3));
    constexpr ivec scalar = ([]() {
        ivec vec(2);
        vec |= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec3 |= - Scalar", scalar, ivec(3));

    KRYS_EXPECT_EQUAL("Vec3 | - Vector", ivec(2) | ivec(1), ivec(3));
    constexpr ivec vec = ([]() {
        ivec vec(2);
        vec |= ivec(1);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec3 |= - Vector", vec, ivec(3));
  }

  static void Test_Vec3_Bitwise_Xor()
  {
    using ivec = vec3_t<int>;

    KRYS_EXPECT_EQUAL("Vec3 ^ - Scalar", ivec(2) ^ 1, ivec(3));
    constexpr ivec scalar = ([]() {
        ivec vec(2);
        vec ^= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec3 ^= - Scalar", scalar, ivec(3));

    KRYS_EXPECT_EQUAL("Vec3 ^ - Vector", ivec(2) ^ ivec(1), ivec(3));
    constexpr ivec vec = ([]() {
        ivec vec(5);
        vec ^= ivec(2);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec3 ^= - Vector", vec, ivec(7));
  }

  static void Test_Vec3_Bitwise_And()
  {
    using ivec = vec3_t<int>;

    KRYS_EXPECT_EQUAL("Vec3 & - Scalar", ivec(3) & 1, ivec(1));
    constexpr ivec scalar = ([]() {
        ivec vec(3);
        vec &= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec3 &= - Scalar", scalar, ivec(1));

    KRYS_EXPECT_EQUAL("Vec3 & - Vector", ivec(3) & ivec(1), ivec(1));
    constexpr ivec vec = ([]() {
        ivec vec(7);
        vec &= ivec(3);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec3 &= - Vector", vec, ivec(3));
  }

  static void Test_Vec3_Bitwise_Not()
  {
    using ivec = vec3_t<int>;
    KRYS_EXPECT_EQUAL("Vec3 ~", ~ivec(1), ivec(~1));
  }
}
