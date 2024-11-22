#include "MTL/Vectors/Vec1.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  constexpr void Test_Constructors()
  {
    // Default constructor
    constexpr vec1_t<float> defaultVec;
    KRYS_EXPECT_EQUAL("Default constructor", defaultVec.x, 0.0f);

    // Constructor with scalar
    constexpr vec1_t<float> scalarVec(5.0f);
    KRYS_EXPECT_EQUAL("Constructor with scalar", scalarVec.x, 5.0f);

    // Copy constructor
    constexpr vec1_t<float> v_original(2.5f);
    constexpr vec1_t<float> v_copy(v_original);
    KRYS_EXPECT_EQUAL("Copy constructor", v_copy.x, 2.5f);

    // Move constructor
    constexpr vec1_t<float> v_movable(7.5f);
    constexpr vec1_t<float> v_move(std::move(v_movable));
    KRYS_EXPECT_EQUAL("Move constructor", v_move.x, 7.5f);
  }

  constexpr void Test_EqualityOperators()
  {
    constexpr vec1_t<float> v1(1.0f);
    constexpr vec1_t<float> v2(1.0f);
    constexpr vec1_t<float> v3(2.0f);

    KRYS_EXPECT_TRUE("Equality operator (equal vectors)", v1 == v2);
    KRYS_EXPECT_FALSE("Equality operator (different vectors)", v1 == v3);
    KRYS_EXPECT_FALSE("Inequality operator (equal vectors)", v1 != v2);
    KRYS_EXPECT_TRUE("Inequality operator (different vectors)", v1 != v3);
  }

  constexpr void Test_ElementAccess()
  {
    constexpr vec1_t<float> v(4.4f);
    KRYS_EXPECT_EQUAL("Element access operator", v[0], 4.4f);
    KRYS_EXPECT_EQUAL("Get<0>() function", v.Get<0>(), 4.4f);
    KRYS_EXPECT_EQUAL("GetLength() function", v.GetLength(), 1);
  }

  constexpr void Test_ArithmeticOperators()
  {
    constexpr vec1_t<float> v1(2.0f);
    constexpr vec1_t<float> v2(3.0f);

    constexpr vec1_t<float> addVecs = v1 + v2;
    KRYS_EXPECT_EQUAL("Addition operator (vector + vector)", addVecs.x, 5.0f);

    constexpr vec1_t<float> addScalar = v1 + 2.0f;
    KRYS_EXPECT_EQUAL("Addition operator (vector + scalar)", addScalar.x, 4.0f);

    constexpr vec1_t<float> subVecs = v1 - v2;
    KRYS_EXPECT_EQUAL("Subtraction operator (vector - vector)", subVecs.x, -1.0f);

    constexpr vec1_t<float> subScalar = v1 - 1.0f;
    KRYS_EXPECT_EQUAL("Subtraction operator (vector - scalar)", subScalar.x, 1.0f);

    constexpr vec1_t<float> mulVecs = v1 * v2;
    KRYS_EXPECT_EQUAL("Multiplication operator (vector * vector)", mulVecs.x, 6.0f);

    constexpr vec1_t<float> mulScalar = v1 * 2.0f;
    KRYS_EXPECT_EQUAL("Multiplication operator (vector * scalar)", mulScalar.x, 4.0f);

    constexpr vec1_t<float> divVecs = v1 / v2;
    KRYS_EXPECT_EQUAL("Division operator (vector / vector)", divVecs.x, 2.0f / 3.0f);

    constexpr vec1_t<float> divScalar = v1 / 2.0f;
    KRYS_EXPECT_EQUAL("Division operator (vector / scalar)", divScalar.x, 1.0f);
  }

  constexpr void Test_UnaryOperator()
  {
    constexpr vec1_t<float> v(5.0f);
    constexpr vec1_t<float> negative = -v;
    KRYS_EXPECT_EQUAL("Unary minus operator", negative.x, -5.0f);
  }
}
