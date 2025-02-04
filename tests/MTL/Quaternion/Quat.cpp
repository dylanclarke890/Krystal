#include "MTL/Quaternion/Quat.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using quat_t = quaternion_t<float>;

  static void Test_Quat_Constructors()
  {
    constexpr quat_t empty {};
    KRYS_EXPECT_EQUAL("Quat Default Constructor", empty, quat_t(1, 0, 0, 0));

    constexpr quat_t copy(empty);
    KRYS_EXPECT_EQUAL("Quat Copy Constructor", copy, empty);

    constexpr quat_t move_src(empty);
    constexpr quat_t move_dst(std::move(move_src));
    KRYS_EXPECT_EQUAL("Quat Move Constructor", move_dst, empty);
  }

  static void Test_Quat_Assignment()
  {
    constexpr auto TestCopy = []()
    {
      quat_t a {};
      quat_t b {1, 2, 3, 4};

      a = b;
      return a == quat_t(1, 2, 3, 4);
    };

    constexpr auto TestMove = []()
    {
      quat_t a {};
      quat_t b {1, 2, 3, 4};

      a = std::move(b);
      return a == quat_t(1, 2, 3, 4);
    };

    KRYS_EXPECT_TRUE("Quat Copy Assignment", TestCopy());
    KRYS_EXPECT_TRUE("Quat Move Assignment", TestMove());
  }

  static void Test_Quat_Equality()
  {
    constexpr quat_t a(1, 2, 3, 4);
    constexpr quat_t b(1, 2, 3, 4);
    constexpr quat_t c(5, 6, 7, 8);

    KRYS_EXPECT_TRUE("Quat Equality Comparison - Equal", a == b);
    KRYS_EXPECT_FALSE("Quat Equality Comparison - Not Equal", a == c);
    KRYS_EXPECT_TRUE("Quat Inequality Comparison - Not Equal", a != c);
  }

  static void Test_Quat_Addition()
  {
    constexpr quat_t a(1, 2, 3, 4);
    constexpr quat_t b(5, 6, 7, 8);

    KRYS_EXPECT_EQUAL("Quat Addition", a + b, quat_t(6, 8, 10, 12));
  }

  static void Test_Quat_Subtraction()
  {
    constexpr quat_t a(1, 2, 3, 4);
    constexpr quat_t b(5, 6, 7, 8);

    KRYS_EXPECT_EQUAL("Quat Subtraction", a - b, quat_t(-4, -4, -4, -4));
  }

  static void Test_Quat_Multiplication()
  {
    constexpr quat_t a(1, 2, 3, 4);
    constexpr quat_t b(5, 6, 7, 8);
    constexpr float scalar = 10;

    KRYS_EXPECT_EQUAL("Quat Multiplication", a * b, quat_t(-60, 12, 30, 24));
    KRYS_EXPECT_EQUAL("Quat Scalar Multiplication", a * scalar, quat_t(10, 20, 30, 40));
  }

  static void Test_Quat_Division()
  {
    constexpr quat_t a(1, 2, 3, 4);
    constexpr float scalar = 10;

    KRYS_EXPECT_EQUAL("Quat Scalar Division", a / scalar, quat_t(0.1f, 0.2f, 0.3f, 0.4f));
  }
}