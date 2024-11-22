#include "MTL/Vectors/Vec2.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  constexpr void Test_Constructors()
  {
    // Default constructor
    constexpr vec2_t<float> defaultVec;
    KRYS_EXPECT_EQUAL("Default constructor x", defaultVec.x, 0.0f);
    KRYS_EXPECT_EQUAL("Default constructor y", defaultVec.y, 0.0f);

    // Constructor with scalar
    constexpr vec2_t<float> scalarVec(5.0f);
    KRYS_EXPECT_EQUAL("Constructor with scalar x", scalarVec.x, 5.0f);
    KRYS_EXPECT_EQUAL("Constructor with scalar y", scalarVec.y, 5.0f);

    // Constructor with components
    constexpr vec2_t<float> componentVec(3.0f, 4.0f);
    KRYS_EXPECT_EQUAL("Constructor with components x", componentVec.x, 3.0f);
    KRYS_EXPECT_EQUAL("Constructor with components y", componentVec.y, 4.0f);

    // Copy constructor
    constexpr vec2_t<float> copyVec(componentVec);
    KRYS_EXPECT_EQUAL("Copy constructor x", copyVec.x, 3.0f);
    KRYS_EXPECT_EQUAL("Copy constructor y", copyVec.y, 4.0f);

    // Move constructor
    constexpr vec2_t<float> moveVec(std::move(componentVec));
    KRYS_EXPECT_EQUAL("Move constructor x", moveVec.x, 3.0f);
    KRYS_EXPECT_EQUAL("Move constructor y", moveVec.y, 4.0f);
  }

  constexpr void Test_EqualityOperators()
  {
    constexpr vec2_t<float> v1(1.0f, 2.0f);
    constexpr vec2_t<float> v2(1.0f, 2.0f);
    constexpr vec2_t<float> v3(3.0f, 4.0f);

    KRYS_EXPECT_TRUE("Equality operator (equal vectors)", v1 == v2);
    KRYS_EXPECT_FALSE("Equality operator (different vectors)", v1 == v3);
    KRYS_EXPECT_FALSE("Inequality operator (equal vectors)", v1 != v2);
    KRYS_EXPECT_TRUE("Inequality operator (different vectors)", v1 != v3);
  }

  constexpr void Test_ElementAccess()
  {
    constexpr vec2_t<float> v(3.3f, 4.4f);
    KRYS_EXPECT_EQUAL("Element access operator x", v[0], 3.3f);
    KRYS_EXPECT_EQUAL("Element access operator y", v[1], 4.4f);
    KRYS_EXPECT_EQUAL("Get<0>() function", v.Get<0>(), 3.3f);
    KRYS_EXPECT_EQUAL("Get<1>() function", v.Get<1>(), 4.4f);
    KRYS_EXPECT_EQUAL("GetLength() function", v.GetLength(), 2);
  }

  constexpr void Test_ArithmeticOperators()
  {
    constexpr vec2_t<float> v1(1.0f, 2.0f);
    constexpr vec2_t<float> v2(3.0f, 4.0f);

    // Addition
    constexpr vec2_t<float> addVecs = v1 + v2;
    KRYS_EXPECT_EQUAL("Addition operator x", addVecs.x, 4.0f);
    KRYS_EXPECT_EQUAL("Addition operator y", addVecs.y, 6.0f);

    constexpr vec2_t<float> addScalar = v1 + 2.0f;
    KRYS_EXPECT_EQUAL("Addition operator (vector + scalar) x", addScalar.x, 3.0f);
    KRYS_EXPECT_EQUAL("Addition operator (vector + scalar) y", addScalar.y, 4.0f);

    // Subtraction
    constexpr vec2_t<float> subVecs = v1 - v2;
    KRYS_EXPECT_EQUAL("Subtraction operator x", subVecs.x, -2.0f);
    KRYS_EXPECT_EQUAL("Subtraction operator y", subVecs.y, -2.0f);

    constexpr vec2_t<float> subScalar = v1 - 1.0f;
    KRYS_EXPECT_EQUAL("Subtraction operator (vector - scalar) x", subScalar.x, 0.0f);
    KRYS_EXPECT_EQUAL("Subtraction operator (vector - scalar) y", subScalar.y, 1.0f);

    // Multiplication
    constexpr vec2_t<float> mulVecs = v1 * v2;
    KRYS_EXPECT_EQUAL("Multiplication operator x", mulVecs.x, 3.0f);
    KRYS_EXPECT_EQUAL("Multiplication operator y", mulVecs.y, 8.0f);

    constexpr vec2_t<float> mulScalar = v1 * 2.0f;
    KRYS_EXPECT_EQUAL("Multiplication operator (vector * scalar) x", mulScalar.x, 2.0f);
    KRYS_EXPECT_EQUAL("Multiplication operator (vector * scalar) y", mulScalar.y, 4.0f);

    // Division
    constexpr vec2_t<float> divVecs = v2 / v1;
    KRYS_EXPECT_EQUAL("Division operator x", divVecs.x, 3.0f);
    KRYS_EXPECT_EQUAL("Division operator y", divVecs.y, 2.0f);

    constexpr vec2_t<float> divScalar = v2 / 2.0f;
    KRYS_EXPECT_EQUAL("Division operator (vector / scalar) x", divScalar.x, 1.5f);
    KRYS_EXPECT_EQUAL("Division operator (vector / scalar) y", divScalar.y, 2.0f);
  }

  constexpr void Test_UnaryOperator()
  {
    constexpr vec2_t<float> v(1.0f, -2.0f);
    constexpr vec2_t<float> negative = -v;
    KRYS_EXPECT_EQUAL("Unary minus operator x", negative.x, -1.0f);
    KRYS_EXPECT_EQUAL("Unary minus operator y", negative.y, 2.0f);
  }
}
