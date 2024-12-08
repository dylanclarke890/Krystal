#include "MTL/Matrices/Mat2x3.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using mat_t = Krys::mat2x3_t<float>;

  static void Test_Mat2x3_Constructors()
  {
    constexpr mat_t scalar(1);
    KRYS_EXPECT_EQUAL("Mat2x3 Scalar Constructor", scalar, mat_t({1, 1}, {1, 1}, {1, 1}));

    constexpr mat_t copy(scalar);
    KRYS_EXPECT_EQUAL("Mat2x3 Copy Constructor", copy, scalar);

    constexpr mat_t move_src(scalar);
    constexpr mat_t move_dst(std::move(move_src));
    KRYS_EXPECT_EQUAL("Mat2x3 Move Constructor", move_dst, scalar);
  }

  static void Test_Mat2x3_Assignment()
  {
    constexpr auto TestCopy = []()
    {
      mat_t a {};
      mat_t b {5, 3, 1, 2, 4, 5};

      a = b;
      return a == mat_t(5, 3, 1, 2, 4, 5);
    };

    constexpr auto TestMove = []()
    {
      mat_t a {};
      mat_t b {5, 3, 1, 2, 4, 5};

      a = std::move(b);
      return a == mat_t(5, 3, 1, 2, 4, 5);
    };

    constexpr auto TestIndexAssignment = []()
    {
      mat_t a {};

      a[0] = {5, 3};
      a[1] = {1, 2};
      a[2] = {4, 5};

      return a == mat_t(5, 3, 1, 2, 4, 5);
    };

    constexpr auto TestGetAssignment = []()
    {
      mat_t a {};

      a.Get<0>() = {5, 3};
      a.Get<1>() = {1, 2};
      a.Get<2>() = {4, 5};

      return a == mat_t(5, 3, 1, 2, 4, 5);
    };

    KRYS_EXPECT_TRUE("Mat2x3 Copy Assignment", TestCopy());
    KRYS_EXPECT_TRUE("Mat2x3 Move Assignment", TestMove());
    KRYS_EXPECT_TRUE("Mat2x3 Index Assignment", TestIndexAssignment());
    KRYS_EXPECT_TRUE("Mat2x3 Get Assignment", TestGetAssignment());
  }

  static void Test_Mat2x3_Equality()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);
    constexpr mat_t unequal(2, 3, 4, 5, 6, 7);

    KRYS_EXPECT_TRUE("Mat2x3 Equality Comparison - Equal", mat == mat);
    KRYS_EXPECT_FALSE("Mat2x3 Equality Comparison - Not Equal", mat == unequal);
    KRYS_EXPECT_TRUE("Mat2x3 Inequality Comparison - Not Equal", mat != unequal);
  }

  static void Test_Mat2x3_ElementAccess()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);
    KRYS_EXPECT_EQUAL("Mat2x3 Element Access [0]", mat[0], Vec2(1, 2));
    KRYS_EXPECT_EQUAL("Mat2x3 Element Access [1]", mat[1], Vec2(3, 4));
    KRYS_EXPECT_EQUAL("Mat2x3 Element Access [2]", mat[2], Vec2(5, 6));
  }

  static void Test_Mat2x3_Unary()
  {
    KRYS_EXPECT_EQUAL("Mat2x3 Unary Negation", -mat_t(1, 2, 3, 4, 5, 6), mat_t(-1, -2, -3, -4, -5, -6));
    KRYS_EXPECT_EQUAL("Mat2x3 Unary Plus", +mat_t(1, -2, 3, -4, 5, -6), mat_t(1, -2, 3, -4, 5, -6));
  }

  static void Test_Mat2x3_Addition()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);

    KRYS_EXPECT_EQUAL("Mat2x3 Matrix Addition", mat + mat_t(9, 8, 7, 6, 5, 4), mat_t(10, 10, 10, 10, 10, 10));
    KRYS_EXPECT_EQUAL("Mat2x3 Scalar Addition", mat + 9.0f, mat_t(10, 11, 12, 13, 14, 15));
  }

  static void Test_Mat2x3_Subtraction()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);

    KRYS_EXPECT_EQUAL("Mat2x3 Matrix Subtraction", mat - mat_t(3, 4, 5, 6, 7, 8),
                      mat_t(-2, -2, -2, -2, -2, -2));
    KRYS_EXPECT_EQUAL("Mat2x3 Scalar Subtraction", mat - 5.0f, mat_t(-4, -3, -2, -1, 0, 1));
  }

  static void Test_Mat2x3_Multiplication()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);
    KRYS_EXPECT_EQUAL("Mat2x3 Scalar Multiplication", mat * 2.0f, mat_t(2, 4, 6, 8, 10, 12));
  }

  static void Test_Mat2x3_Division()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);
    KRYS_EXPECT_EQUAL("Mat2x3 Scalar Division", mat / 2.0f, mat_t(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f));
  }
}
