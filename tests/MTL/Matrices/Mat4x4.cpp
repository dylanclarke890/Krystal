#include "MTL/Matrices/Mat4x4.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using mat_t = Krys::mat4x4_t<float>;

  static void Test_Mat4x4_Constructors()
  {
    constexpr mat_t scalar(1);
    KRYS_EXPECT_EQUAL("Mat4x4 Scalar Constructor", scalar,
                      mat_t({1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}));

    constexpr mat_t copy(scalar);
    KRYS_EXPECT_EQUAL("Mat4x4 Copy Constructor", copy, scalar);

    constexpr mat_t move_src(scalar);
    constexpr mat_t move_dst(std::move(move_src));
    KRYS_EXPECT_EQUAL("Mat4x4 Move Constructor", move_dst, scalar);
  }

  static void Test_Mat4x3_Assignment()
  {
    constexpr auto TestCopy = []()
    {
      mat_t a {};
      mat_t b {5, 3, 1, 2, 4, 5, 2, 5, 1, 2, 2, 2, 3, 1, 3, 1};

      a = b;
      return a == mat_t(5, 3, 1, 2, 4, 5, 2, 5, 1, 2, 2, 2, 3, 1, 3, 1);
    };

    constexpr auto TestMove = []()
    {
      mat_t a {};
      mat_t b {5, 3, 1, 2, 4, 5, 2, 5, 1, 2, 2, 2, 3, 1, 3, 1};

      a = std::move(b);
      return a == mat_t(5, 3, 1, 2, 4, 5, 2, 5, 1, 2, 2, 2, 3, 1, 3, 1);
    };

    constexpr auto TestIndexAssignment = []()
    {
      mat_t a {};

      a[0] = {5, 3, 1, 2};
      a[1] = {4, 5, 2, 5};
      a[2] = {1, 2, 2, 2};
      a[3] = {3, 1, 3, 1};

      return a == mat_t(5, 3, 1, 2, 4, 5, 2, 5, 1, 2, 2, 2, 3, 1, 3, 1);
    };

    constexpr auto TestGetAssignment = []()
    {
      mat_t a {};

      a.Get<0>() = {5, 3, 1, 2};
      a.Get<1>() = {4, 5, 2, 5};
      a.Get<2>() = {1, 2, 2, 2};
      a.Get<3>() = {3, 1, 3, 1};

      return a == mat_t(5, 3, 1, 2, 4, 5, 2, 5, 1, 2, 2, 2, 3, 1, 3, 1);
    };

    KRYS_EXPECT_TRUE("Mat4x4 Copy Assignment", TestCopy());
    KRYS_EXPECT_TRUE("Mat4x4 Move Assignment", TestMove());
    KRYS_EXPECT_TRUE("Mat4x4 Index Assignment", TestIndexAssignment());
    KRYS_EXPECT_TRUE("Mat4x4 Get Assignment", TestGetAssignment());
  }

  static void Test_Mat4x4_Equality()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    constexpr mat_t unequal(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17);

    KRYS_EXPECT_TRUE("Mat4x4 Equality Comparison - Equal", mat == mat);
    KRYS_EXPECT_FALSE("Mat4x4 Equality Comparison - Not Equal", mat == unequal);
    KRYS_EXPECT_TRUE("Mat4x4 Inequality Comparison - Not Equal", mat != unequal);
  }

  static void Test_Mat4x4_ElementAccess()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    KRYS_EXPECT_EQUAL("Mat4x4 Element Access [0]", mat[0], Vec4(1, 2, 3, 4));
    KRYS_EXPECT_EQUAL("Mat4x4 Element Access [1]", mat[1], Vec4(5, 6, 7, 8));
    KRYS_EXPECT_EQUAL("Mat4x4 Element Access [2]", mat[2], Vec4(9, 10, 11, 12));
    KRYS_EXPECT_EQUAL("Mat4x4 Element Access [3]", mat[3], Vec4(13, 14, 15, 16));
  }

  static void Test_Mat4x4_Unary()
  {
    KRYS_EXPECT_EQUAL("Mat4x4 Unary Negation", -mat_t(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
                      mat_t(-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16));
    KRYS_EXPECT_EQUAL("Mat4x4 Unary Plus",
                      +mat_t(1, -2, 3, -4, 5, -6, 7, -8, 9, 10, 11, -12, -13, -14, 15, 16),
                      mat_t(1, -2, 3, -4, 5, -6, 7, -8, 9, 10, 11, -12, -13, -14, 15, 16));
  }

  static void Test_Mat4x4_Addition()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    KRYS_EXPECT_EQUAL("Mat4x4 Matrix Addition",
                      mat + mat_t(9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6),
                      mat_t(10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10));
    KRYS_EXPECT_EQUAL("Mat4x4 Scalar Addition", mat + 9.0f,
                      mat_t(10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25));
  }

  static void Test_Mat4x4_Subtraction()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    KRYS_EXPECT_EQUAL("Mat4x4 Matrix Subtraction",
                      mat - mat_t(3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18),
                      mat_t(-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2));
    KRYS_EXPECT_EQUAL("Mat4x4 Scalar Subtraction", mat - 5.0f,
                      mat_t(-4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11));
  }

  static void Test_Mat4x4_Multiplication()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    KRYS_EXPECT_EQUAL("Mat4x4 Scalar Multiplication", mat * 2.0f,
                      mat_t(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32));
  }

  static void Test_Mat3x3_Multiplication()
  {
    KRYS_EXPECT_EQUAL("Mat4x4 Scalar Multiplication",
                      mat_t({1, 4, 7, 2}, {2, 5, 8, 3}, {3, 6, 9, 4}, {1, 2, 3, 4}) * 2.0f,
                      mat_t({2, 8, 14, 4}, {4, 10, 16, 6}, {6, 12, 18, 8}, {2, 4, 6, 8}));

    constexpr mat_t a({3, 2, 7, 1}, {-2, 6, 1, -3}, {-1, -5, -8, 2}, {3, 5, 1, 2});
    constexpr mat_t b({1, 0, -3, 1}, {9, 11, 2, 2}, {4, 5, -7, 3}, {1, 2, 3, 4});
    KRYS_EXPECT_EQUAL("Mat4x4 Matrix Multiplication", a * b,
                      mat_t({9, 22, 32, -3}, {9, 84, 60, -16}, {18, 88, 92, -19}, {8, 19, -11, 9}));

    constexpr Vec4 v(1, 1, 1, 1);
    constexpr auto result = a * v;
    KRYS_EXPECT_EQUAL("Mat4x4 Vector Multiplication", a * v, Vec4(13, 2, -12, 11));
  }

  static void Test_Mat4x4_Division()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    KRYS_EXPECT_EQUAL(
      "Mat4x4 Scalar Division", mat / 2.0f,
      mat_t(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f));
  }

  static void Test_Mat4x4_Bitwise_ShiftLeft()
  {
    using imat = mat4x4_t<int>;

    KRYS_EXPECT_EQUAL("Mat4x4 << - Scalar", imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) << 1,
                      imat(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2));
    constexpr imat vec = ([]() {
        imat vec(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
        vec <<= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x4 <<= - Scalar", vec, imat(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8));
  }

  static void Test_Mat4x4_Bitwise_ShiftRight()
  {
    using imat = mat4x4_t<int>;

    KRYS_EXPECT_EQUAL("Mat4x4 >> - Scalar", imat(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2) >> 1,
                      imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
    constexpr imat vec = ([]() {
        imat vec(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
        vec >>= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x4 >>= - Scalar", vec, imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
  }

  static void Test_Mat4x4_Bitwise_Or()
  {
    using imat = mat4x4_t<int>;

    KRYS_EXPECT_EQUAL("Mat4x4 | - Scalar", imat(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2) | 1,
                      imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3));
    constexpr imat scalar = ([]() {
        imat vec(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
        vec |= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x4 |= - Scalar", scalar, imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3));

    KRYS_EXPECT_EQUAL("Mat4x4 | - Vector",
                      imat(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2)
                        | imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1),
                      imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3));
    constexpr imat vec = ([]() {
        imat vec(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
        vec |= imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x4 |= - Vector", vec, imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3));
  }

  static void Test_Mat4x4_Bitwise_Xor()
  {
    using imat = mat4x4_t<int>;

    KRYS_EXPECT_EQUAL("Mat4x4 ^ - Scalar", imat(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2) ^ 1,
                      imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3));
    constexpr imat scalar = ([]() {
        imat vec(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
        vec ^= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x4 ^= - Scalar", scalar, imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3));

    KRYS_EXPECT_EQUAL("Mat4x4 ^ - Vector",
                      imat(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2)
                        ^ imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1),
                      imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3));
    constexpr imat vec = ([]() {
        imat vec(5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5);
        vec ^= imat(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x4 ^= - Vector", vec, imat(7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7));
  }

  static void Test_Mat4x4_Bitwise_And()
  {
    using imat = mat4x4_t<int>;

    KRYS_EXPECT_EQUAL("Mat4x4 & - Scalar", imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3) & 1,
                      imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
    constexpr imat scalar = ([]() {
        imat vec(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3);
        vec &= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x4 &= - Scalar", scalar, imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));

    KRYS_EXPECT_EQUAL("Mat4x4 & - Vector",
                      imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3)
                        & imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1),
                      imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
    constexpr imat vec = ([]() {
        imat vec(7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7);
        vec &= imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat4x4 &= - Vector", vec, imat(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3));
  }

  static void Test_Mat4x4_Bitwise_Not()
  {
    using imat = mat4x4_t<int>;
    KRYS_EXPECT_EQUAL("Mat4x4 ~", ~imat(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1),
                      imat(~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1));
  }
}
