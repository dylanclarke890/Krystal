#include "MTL/Vectors/Vec1.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using vec_t = vec1_t<float>;

  static void Test_Vec1_Constructors()
  {
    constexpr vec_t empty {};
    KRYS_EXPECT_EQUAL("Vec1 Default Constructor", empty, vec_t(0));

    constexpr vec_t scalar(1);
    KRYS_EXPECT_EQUAL("Vec1 Scalar Constructor", scalar, vec_t(1));

    constexpr vec_t copy(scalar);
    KRYS_EXPECT_EQUAL("Vec1 Copy Constructor", copy, scalar);

    constexpr vec_t move_src(scalar);
    constexpr vec_t move_dst(std::move(move_src));
    KRYS_EXPECT_EQUAL("Vec1 Move Constructor", move_dst, scalar);
  }

  static void Test_Vec1_Assignment()
  {
    constexpr auto TestCopy = []()
    {
      vec_t a {};
      vec_t b {5};

      a = b;
      return a == vec_t(5);
    };

    constexpr auto TestMove = []()
    {
      vec_t a {};
      vec_t b {5};

      a = std::move(b);
      return a == vec_t(5);
    };

    constexpr auto TestIndexAssignment = []()
    {
      vec_t a {};

      a[0] = 5.0f;
      return a == vec_t(5);
    };

    constexpr auto TestGetAssignment = []()
    {
      vec_t a {};

      a.Get<0>() = 5.0f;
      return a == vec_t(5);
    };

    KRYS_EXPECT_TRUE("Vec1 Copy Assignment", TestCopy());
    KRYS_EXPECT_TRUE("Vec1 Move Assignment", TestMove());
    KRYS_EXPECT_TRUE("Vec1 Index Assignment", TestIndexAssignment());
    KRYS_EXPECT_TRUE("Vec1 Get Assignment", TestGetAssignment());
  }

  static void Test_Vec1_Equality()
  {
    constexpr vec_t vec(1);
    constexpr vec_t unequal(0);

    KRYS_EXPECT_TRUE("Vec1 Equality Comparison - Equal", vec == vec);
    KRYS_EXPECT_FALSE("Vec1 Equality Comparison - Not Equal", vec == unequal);
    KRYS_EXPECT_TRUE("Vec1 Inequality Comparison - Not Equal", vec != unequal);
  }

  static void Test_Vec1_ElementAccess()
  {
    constexpr vec_t vec(1);
    KRYS_EXPECT_EQUAL("Vec1 GetLength()", vec.GetLength(), 1);
    KRYS_EXPECT_EQUAL("Vec1 Element Access [0]", vec[0], 1);
    KRYS_EXPECT_EQUAL("Vec1 Element Access Get<0>()", vec.Get<0>(), 1);
  }

  static void Test_Vec1_Unary()
  {
    KRYS_EXPECT_EQUAL("Vec1 Unary Negation", -vec_t(1), vec_t(-1));
    KRYS_EXPECT_EQUAL("Vec1 Unary Plus", +vec_t(-1), vec_t(-1));
  }

  static void Test_Vec1_Addition()
  {
    constexpr vec_t vec(1);
    KRYS_EXPECT_EQUAL("Vec1 Vector Addition", vec + vec_t(9), vec_t(10));
    KRYS_EXPECT_EQUAL("Vec1 Scalar Addition", vec + 9.0f, vec_t(10));
  }

  static void Test_Vec1_Subtraction()
  {
    constexpr vec_t vec(1);
    KRYS_EXPECT_EQUAL("Vec1 Vector Subtraction", vec - vec_t(9), vec_t(-8));
    KRYS_EXPECT_EQUAL("Vec1 Scalar Subtraction", vec - 9.0f, vec_t(-8));
  }

  static void Test_Vec1_Multiplication()
  {
    constexpr vec_t vec(3);
    KRYS_EXPECT_EQUAL("Vec1 Vector Multiplication", vec * vec_t(5), vec_t(15));
    KRYS_EXPECT_EQUAL("Vec1 Scalar Multiplication", vec * 5.0f, vec_t(15));
  }

  static void Test_Vec1_Division()
  {
    constexpr vec_t vec(2);
    KRYS_EXPECT_EQUAL("Vec1 Vector Division", vec / vec_t(2), vec_t(1));
    KRYS_EXPECT_EQUAL("Vec1 Scalar Division", vec / 4.0f, vec_t(0.5f));
  }

  static void Test_Vec1_Bitwise_ShiftLeft()
  {
    using ivec = vec1_t<int>;

    KRYS_EXPECT_EQUAL("Vec1 << - Scalar", ivec(1) << 1, ivec(2));
    constexpr ivec vec = ([]() {
        ivec vec(1);
        vec <<= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec1 <<= - Scalar", vec, ivec(4));
  }

  static void Test_Vec1_Bitwise_ShiftRight()
  {
    using ivec = vec1_t<int>;

    KRYS_EXPECT_EQUAL("Vec1 >> - Scalar", ivec(2) >> 1, ivec(1));
    constexpr ivec vec = ([]() {
        ivec vec(4);
        vec >>= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec1 >>= - Scalar", vec, ivec(1));
  }

  static void Test_Vec1_Bitwise_Or()
  {
    using ivec = vec1_t<int>;

    KRYS_EXPECT_EQUAL("Vec1 | - Scalar", ivec(2) | 1, ivec(3));
    constexpr ivec scalar = ([]() {
        ivec vec(2);
        vec |= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec1 |= - Scalar", scalar, ivec(3));

    KRYS_EXPECT_EQUAL("Vec1 | - Vector", ivec(2) | ivec(1), ivec(3));
    constexpr ivec vec = ([]() {
        ivec vec(2);
        vec |= ivec(1);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec1 |= - Vector", vec, ivec(3));
  }

  static void Test_Vec1_Bitwise_Xor()
  {
    using ivec = vec1_t<int>;

    KRYS_EXPECT_EQUAL("Vec1 ^ - Scalar", ivec(2) ^ 1, ivec(3));
    constexpr ivec scalar = ([]() {
        ivec vec(2);
        vec ^= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec1 ^= - Scalar", scalar, ivec(3));

    KRYS_EXPECT_EQUAL("Vec1 ^ - Vector", ivec(2) ^ ivec(1), ivec(3));
    constexpr ivec vec = ([]() {
        ivec vec(5);
        vec ^= ivec(2);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec1 ^= - Vector", vec, ivec(7));
  }

  static void Test_Vec1_Bitwise_And()
  {
    using ivec = vec1_t<int>;
    
    KRYS_EXPECT_EQUAL("Vec1 & - Scalar", ivec(3) & 1, ivec(1));
    constexpr ivec scalar = ([]() {
        ivec vec(3);
        vec &= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec1 &= - Scalar", scalar, ivec(1));

    KRYS_EXPECT_EQUAL("Vec1 & - Vector", ivec(3) & ivec(1), ivec(1));
    constexpr ivec vec = ([]() {
        ivec vec(7);
        vec &= ivec(3);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Vec1 &= - Vector", vec, ivec(3));
  }

  static void Test_Vec1_Bitwise_Not()
  {
    using ivec = vec1_t<int>;
    KRYS_EXPECT_EQUAL("Vec1 ~", ~ivec(1), ivec(~1));
  }
}
