#include "MTL/Matrices/Mat4x2.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using mat_t = Krys::mat4x2_t<float>;

  static void Test_Mat4x2_Constructors()
  {
    constexpr mat_t scalar(1);
    KRYS_EXPECT_EQUAL("Mat4x2 Scalar Constructor", scalar, mat_t({1, 1, 1, 1}, {1, 1, 1, 1}));

    constexpr mat_t copy(scalar);
    KRYS_EXPECT_EQUAL("Mat4x2 Copy Constructor", copy, scalar);

    constexpr mat_t move_src(scalar);
    constexpr mat_t move_dst(std::move(move_src));
    KRYS_EXPECT_EQUAL("Mat4x2 Move Constructor", move_dst, scalar);
  }

  static void Test_Mat4x2_Assignment()
  {
    constexpr auto TestCopy = []()
    {
      mat_t a {};
      mat_t b {5, 3, 1, 2, 4, 5, 7, 8};

      a = b;
      return a == mat_t(5, 3, 1, 2, 4, 5, 7, 8);
    };

    constexpr auto TestMove = []()
    {
      mat_t a {};
      mat_t b {5, 3, 1, 2, 4, 5, 7, 8};

      a = std::move(b);
      return a == mat_t(5, 3, 1, 2, 4, 5, 7, 8);
    };

    constexpr auto TestIndexAssignment = []()
    {
      mat_t a {};

      a[0] = {5, 3, 1, 2};
      a[1] = {4, 5, 7, 8};

      return a == mat_t(5, 3, 1, 2, 4, 5, 7, 8);
    };

    constexpr auto TestGetAssignment = []()
    {
      mat_t a {};

      a.Get<0>() = {5, 3, 1, 2};
      a.Get<1>() = {4, 5, 7, 8};

      return a == mat_t(5, 3, 1, 2, 4, 5, 7, 8);
    };

    KRYS_EXPECT_TRUE("Mat4x2 Copy Assignment", TestCopy());
    KRYS_EXPECT_TRUE("Mat4x2 Move Assignment", TestMove());
    KRYS_EXPECT_TRUE("Mat4x2 Index Assignment", TestIndexAssignment());
    KRYS_EXPECT_TRUE("Mat4x2 Get Assignment", TestGetAssignment());
  }

  static void Test_Mat4x2_Equality()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8);
    constexpr mat_t unequal(2, 3, 4, 5, 6, 7, 8, 9);

    KRYS_EXPECT_TRUE("Mat4x2 Equality Comparison - Equal", mat == mat);
    KRYS_EXPECT_FALSE("Mat4x2 Equality Comparison - Not Equal", mat == unequal);
    KRYS_EXPECT_TRUE("Mat4x2 Inequality Comparison - Not Equal", mat != unequal);
  }

  static void Test_Mat4x2_ElementAccess()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8);
    KRYS_EXPECT_EQUAL("Mat4x2 Element Access [0]", mat[0], Vec4(1, 2, 3, 4));
    KRYS_EXPECT_EQUAL("Mat4x2 Element Access [1]", mat[1], Vec4(5, 6, 7, 8));
  }

  static void Test_Mat4x2_Unary()
  {
    KRYS_EXPECT_EQUAL("Mat4x2 Unary Negation", -mat_t(1, 2, 3, 4, 5, 6, 7, 8),
                      mat_t(-1, -2, -3, -4, -5, -6, -7, -8));
    KRYS_EXPECT_EQUAL("Mat4x2 Unary Plus", +mat_t(1, -2, 3, -4, 5, -6, -7, 8),
                      mat_t(1, -2, 3, -4, 5, -6, -7, 8));
  }

  static void Test_Mat4x2_Addition()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8);

    KRYS_EXPECT_EQUAL("Mat4x2 Matrix Addition", mat + mat_t(9, 8, 7, 6, 5, 4, 3, 2),
                      mat_t(10, 10, 10, 10, 10, 10, 10, 10));
    KRYS_EXPECT_EQUAL("Mat4x2 Scalar Addition", mat + 9.0f, mat_t(10, 11, 12, 13, 14, 15, 16, 17));
  }

  static void Test_Mat4x2_Subtraction()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8);

    KRYS_EXPECT_EQUAL("Mat4x2 Matrix Subtraction", mat - mat_t(3, 4, 5, 6, 7, 8, 9, 10),
                      mat_t(-2, -2, -2, -2, -2, -2, -2, -2));
    KRYS_EXPECT_EQUAL("Mat4x2 Scalar Subtraction", mat - 5.0f, mat_t(-4, -3, -2, -1, 0, 1, 2, 3));
  }

  static void Test_Mat4x2_Multiplication()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8);
    KRYS_EXPECT_EQUAL("Mat4x2 Scalar Multiplication", mat * 2.0f, mat_t(2, 4, 6, 8, 10, 12, 14, 16));
  }

  static void Test_Mat4x2_Division()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8);
    KRYS_EXPECT_EQUAL("Mat4x2 Scalar Division", mat / 2.0f,
                      mat_t(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f));
  }

  static void Test_Mat4x2_Bitwise_ShiftLeft()
  {
    using imat = mat4x2_t<int>;

    KRYS_EXPECT_EQUAL("Mat4x2 << - Scalar", imat(1) << 1, imat(2));
    constexpr imat vec = ([]() {
        imat vec(1);
        vec <<= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x2 <<= - Scalar", vec, imat(4));
  }

  static void Test_Mat4x2_Bitwise_ShiftRight()
  {
    using imat = mat4x2_t<int>;

    KRYS_EXPECT_EQUAL("Mat4x2 >> - Scalar", imat(2) >> 1, imat(1));
    constexpr imat vec = ([]() {
        imat vec(4);
        vec >>= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x2 >>= - Scalar", vec, imat(1));
  }

  static void Test_Mat4x2_Bitwise_Or()
  {
    using imat = mat4x2_t<int>;

    KRYS_EXPECT_EQUAL("Mat4x2 | - Scalar", imat(2) | 1, imat(3));
    constexpr imat scalar = ([]() {
        imat vec(2);
        vec |= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x2 |= - Scalar", scalar, imat(3));

    KRYS_EXPECT_EQUAL("Mat4x2 | - Vector", imat(2) | imat(1), imat(3));
    constexpr imat vec = ([]() {
        imat vec(2);
        vec |= imat(1);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x2 |= - Vector", vec, imat(3));
  }

  static void Test_Mat4x2_Bitwise_Xor()
  {
    using imat = mat4x2_t<int>;

    KRYS_EXPECT_EQUAL("Mat4x2 ^ - Scalar", imat(2) ^ 1, imat(3));
    constexpr imat scalar = ([]() {
        imat vec(2);
        vec ^= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x2 ^= - Scalar", scalar, imat(3));

    KRYS_EXPECT_EQUAL("Mat4x2 ^ - Vector", imat(2) ^ imat(1), imat(3));
    constexpr imat vec = ([]() {
        imat vec(5);
        vec ^= imat(2);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x2 ^= - Vector", vec, imat(7));
  }

  static void Test_Mat4x2_Bitwise_And()
  {
    using imat = mat4x2_t<int>;

    KRYS_EXPECT_EQUAL("Mat4x2 & - Scalar", imat(3) & 1, imat(1));
    constexpr imat scalar = ([]() {
        imat vec(3);
        vec &= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x2 &= - Scalar", scalar, imat(1));

    KRYS_EXPECT_EQUAL("Mat4x2 & - Vector", imat(3) & imat(1), imat(1));
    constexpr imat vec = ([]() {
        imat vec(7);
        vec &= imat(3);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x2 &= - Vector", vec, imat(3));
  }

  static void Test_Mat4x2_Bitwise_Not()
  {
    using imat = mat4x2_t<int>;
    KRYS_EXPECT_EQUAL("Mat4x2 ~", ~imat(1), imat(~1));
  }
}
