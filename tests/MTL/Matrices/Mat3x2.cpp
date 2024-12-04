#include "MTL/Matrices/Mat3x2.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using mat_t = Krys::mat3x2_t<float>;

  static void Test_Mat3x2_Constructors()
  {
    constexpr mat_t scalar(1);
    KRYS_EXPECT_EQUAL("Mat3x2 Scalar Constructor", scalar, mat_t({1, 1, 1}, {1, 1, 1}));

    constexpr mat_t copy(scalar);
    KRYS_EXPECT_EQUAL("Mat3x2 Copy Constructor", copy, scalar);

    constexpr mat_t move_src(scalar);
    constexpr mat_t move_dst(std::move(move_src));
    KRYS_EXPECT_EQUAL("Mat3x2 Move Constructor", move_dst, scalar);
  }

  static void Test_Mat3x2_Equality()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);
    constexpr mat_t unequal(2, 3, 4, 5, 6, 7);

    KRYS_EXPECT_TRUE("Mat3x2 Equality Comparison - Equal", mat == mat);
    KRYS_EXPECT_FALSE("Mat3x2 Equality Comparison - Not Equal", mat == unequal);
    KRYS_EXPECT_TRUE("Mat3x2 Inequality Comparison - Not Equal", mat != unequal);
  }

  static void Test_Mat3x2_ElementAccess()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);
    KRYS_EXPECT_EQUAL("Mat3x2 Element Access [0]", mat[0], Vec3(1, 2, 3));
    KRYS_EXPECT_EQUAL("Mat3x2 Element Access [1]", mat[1], Vec3(4, 5, 6));
  }

  static void Test_Mat3x2_Unary()
  {
    KRYS_EXPECT_EQUAL("Mat3x2 Unary Negation", -mat_t(1, 2, 3, 4, 5, 6), mat_t(-1, -2, -3, -4, -5, -6));
    KRYS_EXPECT_EQUAL("Mat3x2 Unary Plus", +mat_t(1, -2, 3, -4, 5, -6), mat_t(1, -2, 3, -4, 5, -6));
  }

  static void Test_Mat3x2_Addition()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);

    KRYS_EXPECT_EQUAL("Mat3x2 Matrix Addition", mat + mat_t(9, 8, 7, 6, 5, 4), mat_t(10, 10, 10, 10, 10, 10));
    KRYS_EXPECT_EQUAL("Mat3x2 Scalar Addition", mat + 9.0f, mat_t(10, 11, 12, 13, 14, 15));
  }

  static void Test_Mat3x2_Subtraction()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);

    KRYS_EXPECT_EQUAL("Mat3x2 Matrix Subtraction", mat - mat_t(3, 4, 5, 6, 7, 8),
                      mat_t(-2, -2, -2, -2, -2, -2));
    KRYS_EXPECT_EQUAL("Mat3x2 Scalar Subtraction", mat - 5.0f, mat_t(-4, -3, -2, -1, 0, 1));
  }

  static void Test_Mat3x2_Multiplication()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);
    KRYS_EXPECT_EQUAL("Mat3x2 Scalar Multiplication", mat * 2.0f, mat_t(2, 4, 6, 8, 10, 12));
  }

  static void Test_Mat3x2_Division()
  {
    constexpr mat_t mat(1, 2, 3, 4, 5, 6);
    KRYS_EXPECT_EQUAL("Mat3x2 Scalar Division", mat / 2.0f, mat_t(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f));
  }
}
