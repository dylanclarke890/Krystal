#include "MTL/Vectors/Vec4.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using vec_t = vec4_t<float>;

  static void Test_Vec4_Constructors()
  {
    constexpr vec_t empty(0);
    KRYS_EXPECT_EQUAL("Vec4 Default Constructor", empty, vec_t(0, 0, 0, 0));

    constexpr vec_t scalar(1);
    KRYS_EXPECT_EQUAL("Vec4 Scalar Constructor", scalar, vec_t(1, 1, 1, 1));

    constexpr vec_t copy(scalar);
    KRYS_EXPECT_EQUAL("Vec4 Copy Constructor", copy, scalar);

    constexpr vec_t move_src(scalar);
    constexpr vec_t move_dst(std::move(move_src));
    KRYS_EXPECT_EQUAL("Vec4 Move Constructor", move_dst, scalar);
  }

  static void Test_Vec4_Assignment()
  {
    constexpr auto TestCopy = []()
    {
      vec_t a {};
      vec_t b {5, 3, 2, 1};

      a = b;
      return a == vec_t(5, 3, 2, 1);
    };

    constexpr auto TestMove = []()
    {
      vec_t a {};
      vec_t b {5, 3, 2, 1};

      a = std::move(b);
      return a == vec_t(5, 3, 2, 1);
    };

    constexpr auto TestIndexAssignment = []()
    {
      vec_t a {};

      a[0] = 5.0f;
      a[1] = 3.0f;
      a[2] = 2.0f;
      a[3] = 1.0f;
      return a == vec_t(5, 3, 2, 1);
    };

    constexpr auto TestGetAssignment = []()
    {
      vec_t a {};

      a.Get<0>() = 5.0f;
      a.Get<1>() = 3.0f;
      a.Get<2>() = 2.0f;
      a.Get<3>() = 1.0f;
      return a == vec_t(5, 3, 2, 1);
    };

    KRYS_EXPECT_TRUE("Vec4 Copy Assignment", TestCopy());
    KRYS_EXPECT_TRUE("Vec4 Move Assignment", TestMove());
    KRYS_EXPECT_TRUE("Vec4 Index Assignment", TestIndexAssignment());
    KRYS_EXPECT_TRUE("Vec4 Get Assignment", TestGetAssignment());
  }

  static void Test_Vec4_Equality()
  {
    constexpr vec_t vec(1, 0, 3, 4);
    constexpr vec_t unequal(0, 1, 2, 4);

    KRYS_EXPECT_TRUE("Vec4 Equality Comparison - Equal", vec == vec);
    KRYS_EXPECT_FALSE("Vec4 Equality Comparison - Not Equal", vec == unequal);
    KRYS_EXPECT_TRUE("Vec4 Inequality Comparison - Not Equal", vec != unequal);
  }

  static void Test_Vec4_ElementAccess()
  {
    constexpr vec_t vec(1, 2, 3, 4);
    KRYS_EXPECT_EQUAL("Vec4 GetLength()", vec.GetLength(), 4);

    KRYS_EXPECT_EQUAL("Vec4 Element Access [0]", vec[0], 1);
    KRYS_EXPECT_EQUAL("Vec4 Element Access [1]", vec[1], 2);
    KRYS_EXPECT_EQUAL("Vec4 Element Access [2]", vec[2], 3);
    KRYS_EXPECT_EQUAL("Vec4 Element Access [3]", vec[3], 4);

    KRYS_EXPECT_EQUAL("Vec4 Element Access Get<0>()", vec.Get<0>(), 1);
    KRYS_EXPECT_EQUAL("Vec4 Element Access Get<1>()", vec.Get<1>(), 2);
    KRYS_EXPECT_EQUAL("Vec4 Element Access Get<2>()", vec.Get<2>(), 3);
    KRYS_EXPECT_EQUAL("Vec4 Element Access Get<2>()", vec.Get<3>(), 4);
  }

  static void Test_Vec4_Unary()
  {
    KRYS_EXPECT_EQUAL("Vec4 Unary Negation", -vec_t(1, 3, 5, 7), vec_t(-1, -3, -5, -7));
    KRYS_EXPECT_EQUAL("Vec4 Unary Plus", +vec_t(-1, 3, -5, 7), vec_t(-1, 3, -5, 7));
  }

  static void Test_Vec4_Addition()
  {
    constexpr vec_t vec(1, 2, 3, 4);
    KRYS_EXPECT_EQUAL("Vec4 Vector Addition", vec + vec_t(9, 8, 7, 6), vec_t(10));
    KRYS_EXPECT_EQUAL("Vec4 Scalar Addition", vec + 9.0f, vec_t(10, 11, 12, 13));
  }

  static void Test_Vec4_Subtraction()
  {
    constexpr vec_t vec(1, 2, 3, 4);
    KRYS_EXPECT_EQUAL("Vec4 Vector Subtraction", vec - vec_t(9, 10, 11, 12), vec_t(-8, -8, -8, -8));
    KRYS_EXPECT_EQUAL("Vec4 Scalar Subtraction", vec - 9.0f, vec_t(-8, -7, -6, -5));
  }

  static void Test_Vec4_Multiplication()
  {
    constexpr vec_t vec(3, 4, 5, 6);
    KRYS_EXPECT_EQUAL("Vec4 Vector Multiplication", vec * vec_t(5, 2, 4, 3), vec_t(15, 8, 20, 18));
    KRYS_EXPECT_EQUAL("Vec4 Scalar Multiplication", vec * 5.0f, vec_t(15, 20, 25, 30));
  }

  static void Test_Vec4_Division()
  {
    constexpr vec_t vec(2, 4, 6, 8);
    KRYS_EXPECT_EQUAL("Vec4 Vector Division", vec / vec_t(2, 4, 6, 8), vec_t(1, 1, 1, 1));
    KRYS_EXPECT_EQUAL("Vec4 Scalar Division", vec / 4.0f, vec_t(0.5f, 1, 1.5f, 2));
  }

  static void Test_Vec4_Bitwise_ShiftLeft()
  {
    using ivec = vec4_t<int>;

    KRYS_EXPECT_EQUAL("Vec4 << - Scalar", ivec(1) << 1, ivec(2));
    constexpr ivec vec = ([]() {
        ivec vec(1);
        vec <<= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec4 <<= - Scalar", vec, ivec(4));
  }

  static void Test_Vec4_Bitwise_ShiftRight()
  {
    using ivec = vec4_t<int>;

    KRYS_EXPECT_EQUAL("Vec4 >> - Scalar", ivec(2) >> 1, ivec(1));
    constexpr ivec vec = ([]() {
        ivec vec(4);
        vec >>= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec4 >>= - Scalar", vec, ivec(1));
  }

  static void Test_Vec4_Bitwise_Or()
  {
    using ivec = vec4_t<int>;

    KRYS_EXPECT_EQUAL("Vec4 | - Scalar", ivec(2) | 1, ivec(3));
    constexpr ivec scalar = ([]() {
        ivec vec(2);
        vec |= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec4 |= - Scalar", scalar, ivec(3));

    KRYS_EXPECT_EQUAL("Vec4 | - Vector", ivec(2) | ivec(1), ivec(3));
    constexpr ivec vec = ([]() {
        ivec vec(2);
        vec |= ivec(1);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec4 |= - Vector", vec, ivec(3));
  }

  static void Test_Vec4_Bitwise_Xor()
  {
    using ivec = vec4_t<int>;

    KRYS_EXPECT_EQUAL("Vec4 ^ - Scalar", ivec(2) ^ 1, ivec(3));
    constexpr ivec scalar = ([]() {
        ivec vec(2);
        vec ^= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec4 ^= - Scalar", scalar, ivec(3));

    KRYS_EXPECT_EQUAL("Vec4 ^ - Vector", ivec(2) ^ ivec(1), ivec(3));
    constexpr ivec vec = ([]() {
        ivec vec(5);
        vec ^= ivec(2);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec4 ^= - Vector", vec, ivec(7));
  }

  static void Test_Vec4_Bitwise_And()
  {
    using ivec = vec4_t<int>;

    KRYS_EXPECT_EQUAL("Vec4 & - Scalar", ivec(3) & 1, ivec(1));
    constexpr ivec scalar = ([]() {
        ivec vec(3);
        vec &= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec4 &= - Scalar", scalar, ivec(1));

    KRYS_EXPECT_EQUAL("Vec4 & - Vector", ivec(3) & ivec(1), ivec(1));
    constexpr ivec vec = ([]() {
        ivec vec(7);
        vec &= ivec(3);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec4 &= - Vector", vec, ivec(3));
  }

  static void Test_Vec4_Bitwise_Not()
  {
    using ivec = vec4_t<int>;
    KRYS_EXPECT_EQUAL("Vec4 ~", ~ivec(1), ivec(~1));
  }
}
