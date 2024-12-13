#include "MTL/Matrices/Mat3x3.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using mat_t = Krys::mat3x3_t<float>;

  static void Test_Mat3x3_Constructors()
  {
    constexpr mat_t scalar(1);
    KRYS_EXPECT_EQUAL("Mat3x3 Scalar Constructor", scalar, mat_t({1, 0, 0}, {0, 1, 0}, {0, 0, 1}));

    constexpr mat_t copy(scalar);
    KRYS_EXPECT_EQUAL("Mat3x3 Copy Constructor", copy, scalar);

    constexpr mat_t move_src(scalar);
    constexpr mat_t move_dst(std::move(move_src));
    KRYS_EXPECT_EQUAL("Mat3x3 Move Constructor", move_dst, scalar);
  }

  static void Test_Mat3x3_Assignment()
  {
    constexpr auto TestCopy = []()
    {
      mat_t a {};
      mat_t b {5, 3, 1, 2, 4, 5, 2, 5, 1};

      a = b;
      return a == mat_t(5, 3, 1, 2, 4, 5, 2, 5, 1);
    };

    constexpr auto TestMove = []()
    {
      mat_t a {};
      mat_t b {5, 3, 1, 2, 4, 5, 2, 5, 1};

      a = std::move(b);
      return a == mat_t(5, 3, 1, 2, 4, 5, 2, 5, 1);
    };

    constexpr auto TestIndexAssignment = []()
    {
      mat_t a {};

      a[0] = {5, 3, 1};
      a[1] = {2, 4, 5};
      a[2] = {2, 5, 1};

      return a == mat_t(5, 3, 1, 2, 4, 5, 2, 5, 1);
    };

    constexpr auto TestGetAssignment = []()
    {
      mat_t a {};

      a.Get<0>() = {5, 3, 1};
      a.Get<1>() = {2, 4, 5};
      a.Get<2>() = {2, 5, 1};

      return a == mat_t(5, 3, 1, 2, 4, 5, 2, 5, 1);
    };

    KRYS_EXPECT_TRUE("Mat3x3 Copy Assignment", TestCopy());
    KRYS_EXPECT_TRUE("Mat3x3 Move Assignment", TestMove());
    KRYS_EXPECT_TRUE("Mat3x3 Index Assignment", TestIndexAssignment());
    KRYS_EXPECT_TRUE("Mat3x3 Get Assignment", TestGetAssignment());
  }

  static void Test_Mat3x3_Equality()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9);
    constexpr mat_t unequal(2, 3, 4, 5, 6, 7, 8, 9, 10);

    KRYS_EXPECT_TRUE("Mat3x3 Equality Comparison - Equal", mat == mat);
    KRYS_EXPECT_FALSE("Mat3x3 Equality Comparison - Not Equal", mat == unequal);
    KRYS_EXPECT_TRUE("Mat3x3 Inequality Comparison - Not Equal", mat != unequal);
  }

  static void Test_Mat3x3_ElementAccess()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9);
    KRYS_EXPECT_EQUAL("Mat3x3 Element Access [0]", mat[0], Vec3(1, 2, 3));
    KRYS_EXPECT_EQUAL("Mat3x3 Element Access [1]", mat[1], Vec3(4, 5, 6));
    KRYS_EXPECT_EQUAL("Mat3x3 Element Access [2]", mat[2], Vec3(7, 8, 9));
  }

  static void Test_Mat3x3_Unary()
  {
    KRYS_EXPECT_EQUAL("Mat3x3 Unary Negation", -mat_t(1, 2, 3, 4, 5, 6, 7, 8, 9),
                      mat_t(-1, -2, -3, -4, -5, -6, -7, -8, -9));
    KRYS_EXPECT_EQUAL("Mat3x3 Unary Plus", +mat_t(1, -2, 3, -4, 5, -6, 7, -8, 9),
                      mat_t(1, -2, 3, -4, 5, -6, 7, -8, 9));
  }

  static void Test_Mat3x3_Addition()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9);

    KRYS_EXPECT_EQUAL("Mat3x3 Matrix Addition", mat + mat_t(9, 8, 7, 6, 5, 4, 3, 2, 1),
                      mat_t(10, 10, 10, 10, 10, 10, 10, 10, 10));
    KRYS_EXPECT_EQUAL("Mat3x3 Scalar Addition", mat + 9.0f, mat_t(10, 11, 12, 13, 14, 15, 16, 17, 18));
  }

  static void Test_Mat3x3_Subtraction()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9);

    KRYS_EXPECT_EQUAL("Mat3x3 Matrix Subtraction", mat - mat_t(3, 4, 5, 6, 7, 8, 9, 10, 11),
                      mat_t(-2, -2, -2, -2, -2, -2, -2, -2, -2));
    KRYS_EXPECT_EQUAL("Mat3x3 Scalar Subtraction", mat - 5.0f, mat_t(-4, -3, -2, -1, 0, 1, 2, 3, 4));
  }

  static void Test_Mat3x3_Multiplication()
  {
    KRYS_EXPECT_EQUAL("Mat3x3 Scalar Multiplication", mat_t({1, 4, 7}, {2, 5, 8}, {3, 6, 9}) * 2.0f,
                      mat_t({2, 8, 14}, {4, 10, 16}, {6, 12, 18}));

    constexpr mat_t a({3, 2, 7}, {-2, 6, 1}, {-1, -5, -8});
    constexpr mat_t b({1, 0, -3}, {9, 11, 2}, {4, 5, -7});
    KRYS_EXPECT_EQUAL("Mat3x3 Matrix Multiplication", a * b, mat_t({6, 17, 31}, {3, 74, 58}, {9, 73, 89}));

    constexpr Vec3 v(1, 1, 1);
    KRYS_EXPECT_EQUAL("Mat3x3 Vector Multiplication", a * v, Vec3(12, 5, -14));
  }

  static void Test_Mat3x3_Division()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6, 7, 8, 9);
    KRYS_EXPECT_EQUAL("Mat3x3 Scalar Division", mat / 2.0f,
                      mat_t(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f));
  }

  static void Test_Mat3x3_Bitwise_ShiftLeft()
  {
    using imat = mat3x3_t<int>;

    KRYS_EXPECT_EQUAL("Mat3x3 << - Scalar", imat(1, 1, 1, 1, 1, 1, 1, 1, 1) << 1,
                      imat(2, 2, 2, 2, 2, 2, 2, 2, 2));
    constexpr imat vec = ([]() {
        imat vec(1, 1, 1, 1, 1, 1, 1, 1, 1);
        vec <<= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat3x3 <<= - Scalar", vec, imat(4, 4, 4, 4, 4, 4, 4, 4, 4));
  }

  static void Test_Mat3x3_Bitwise_ShiftRight()
  {
    using imat = mat3x3_t<int>;

    KRYS_EXPECT_EQUAL("Mat3x3 >> - Scalar", imat(2, 2, 2, 2, 2, 2, 2, 2, 2) >> 1,
                      imat(1, 1, 1, 1, 1, 1, 1, 1, 1));
    constexpr imat vec = ([]() {
        imat vec(4, 4, 4, 4, 4, 4, 4, 4, 4);
        vec >>= 2;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat3x3 >>= - Scalar", vec, imat(1, 1, 1, 1, 1, 1, 1, 1, 1));
  }

  static void Test_Mat3x3_Bitwise_Or()
  {
    using imat = mat3x3_t<int>;

    KRYS_EXPECT_EQUAL("Mat3x3 | - Scalar", imat(2, 2, 2, 2, 2, 2, 2, 2, 2) | 1,
                      imat(3, 3, 3, 3, 3, 3, 3, 3, 3));
    constexpr imat scalar = ([]() {
        imat vec(2, 2, 2, 2, 2, 2, 2, 2, 2);
        vec |= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat3x3 |= - Scalar", scalar, imat(3, 3, 3, 3, 3, 3, 3, 3, 3));

    KRYS_EXPECT_EQUAL("Mat3x3 | - Vector", imat(2, 2, 2, 2, 2, 2, 2, 2, 2) | imat(1, 1, 1, 1, 1, 1, 1, 1, 1),
                      imat(3, 3, 3, 3, 3, 3, 3, 3, 3));
    constexpr imat vec = ([]() {
        imat vec(2, 2, 2, 2, 2, 2, 2, 2, 2);
        vec |= imat(1, 1, 1, 1, 1, 1, 1, 1, 1);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat3x3 |= - Vector", vec, imat(3, 3, 3, 3, 3, 3, 3, 3, 3));
  }

  static void Test_Mat3x3_Bitwise_Xor()
  {
    using imat = mat3x3_t<int>;

    KRYS_EXPECT_EQUAL("Mat3x3 ^ - Scalar", imat(2, 2, 2, 2, 2, 2, 2, 2, 2) ^ 1,
                      imat(3, 3, 3, 3, 3, 3, 3, 3, 3));
    constexpr imat scalar = ([]() {
        imat vec(2, 2, 2, 2, 2, 2, 2, 2, 2);
        vec ^= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat3x3 ^= - Scalar", scalar, imat(3, 3, 3, 3, 3, 3, 3, 3, 3));

    KRYS_EXPECT_EQUAL("Mat3x3 ^ - Vector", imat(2, 2, 2, 2, 2, 2, 2, 2, 2) ^ imat(1, 1, 1, 1, 1, 1, 1, 1, 1),
                      imat(3, 3, 3, 3, 3, 3, 3, 3, 3));
    constexpr imat vec = ([]() {
        imat vec(5, 5, 5, 5, 5, 5, 5, 5, 5);
        vec ^= imat(2, 2, 2, 2, 2, 2, 2, 2, 2);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat3x3 ^= - Vector", vec, imat(7, 7, 7, 7, 7, 7, 7, 7, 7));
  }

  static void Test_Mat3x3_Bitwise_And()
  {
    using imat = mat3x3_t<int>;

    KRYS_EXPECT_EQUAL("Mat3x3 & - Scalar", imat(3) & 1, imat(1));
    constexpr imat scalar = ([]() {
        imat vec(3);
        vec &= 1;
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat3x3 &= - Scalar", scalar, imat(1));

    KRYS_EXPECT_EQUAL("Mat3x3 & - Vector", imat(3) & imat(1), imat(1));
    constexpr imat vec = ([]() {
        imat vec(7);
        vec &= imat(3);
        return vec;
      })();
    KRYS_EXPECT_EQUAL("Mat3x3 &= - Vector", vec, imat(3));
  }

  static void Test_Mat3x3_Bitwise_Not()
  {
    using imat = mat3x3_t<int>;
    KRYS_EXPECT_EQUAL("Mat3x3 ~", ~imat(1, 1, 1, 1, 1, 1, 1, 1, 1), imat(~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1, ~1));
  }
}
