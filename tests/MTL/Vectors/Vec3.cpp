#include "MTL/Vectors/Vec3.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  constexpr void Test_Constructors()
  {
    // Default constructor
    constexpr vec3_t<float> defaultVec;
    KRYS_EXPECT_EQUAL("Default constructor x", defaultVec.x, 0.0f);
    KRYS_EXPECT_EQUAL("Default constructor y", defaultVec.y, 0.0f);
    KRYS_EXPECT_EQUAL("Default constructor z", defaultVec.z, 0.0f);

    // Constructor with scalar
    constexpr vec3_t<float> scalarVec(5.0f);
    KRYS_EXPECT_EQUAL("Constructor with scalar x", scalarVec.x, 5.0f);
    KRYS_EXPECT_EQUAL("Constructor with scalar y", scalarVec.y, 5.0f);
    KRYS_EXPECT_EQUAL("Constructor with scalar z", scalarVec.z, 5.0f);

    // Constructor with components
    constexpr vec3_t<float> componentVec(3.0f, 4.0f, 5.0f);
    KRYS_EXPECT_EQUAL("Constructor with components x", componentVec.x, 3.0f);
    KRYS_EXPECT_EQUAL("Constructor with components y", componentVec.y, 4.0f);
    KRYS_EXPECT_EQUAL("Constructor with components z", componentVec.z, 5.0f);

    // Copy constructor
    constexpr vec3_t<float> copyVec(componentVec);
    KRYS_EXPECT_EQUAL("Copy constructor x", copyVec.x, 3.0f);
    KRYS_EXPECT_EQUAL("Copy constructor y", copyVec.y, 4.0f);
    KRYS_EXPECT_EQUAL("Copy constructor z", copyVec.z, 5.0f);

    // Move constructor
    constexpr vec3_t<float> moveVec(std::move(componentVec));
    KRYS_EXPECT_EQUAL("Move constructor x", moveVec.x, 3.0f);
    KRYS_EXPECT_EQUAL("Move constructor y", moveVec.y, 4.0f);
    KRYS_EXPECT_EQUAL("Move constructor z", moveVec.z, 5.0f);
  }

  constexpr void Test_EqualityOperators()
  {
    constexpr vec3_t<float> v1(1.0f, 2.0f, 3.0f);
    constexpr vec3_t<float> v2(1.0f, 2.0f, 3.0f);
    constexpr vec3_t<float> v3(4.0f, 5.0f, 6.0f);

    KRYS_EXPECT_TRUE("Equality operator (equal vectors)", v1 == v2);
    KRYS_EXPECT_FALSE("Equality operator (different vectors)", v1 == v3);
    KRYS_EXPECT_FALSE("Inequality operator (equal vectors)", v1 != v2);
    KRYS_EXPECT_TRUE("Inequality operator (different vectors)", v1 != v3);
  }

  constexpr void Test_ElementAccess()
  {
    constexpr vec3_t<float> v(3.3f, 4.4f, 5.5f);
    KRYS_EXPECT_EQUAL("Element access operator x", v[0], 3.3f);
    KRYS_EXPECT_EQUAL("Element access operator y", v[1], 4.4f);
    KRYS_EXPECT_EQUAL("Element access operator z", v[2], 5.5f);
    KRYS_EXPECT_EQUAL("Get<0>() function", v.Get<0>(), 3.3f);
    KRYS_EXPECT_EQUAL("Get<1>() function", v.Get<1>(), 4.4f);
    KRYS_EXPECT_EQUAL("Get<2>() function", v.Get<2>(), 5.5f);
    KRYS_EXPECT_EQUAL("GetLength() function", v.GetLength(), 3);
  }

  constexpr void Test_ArithmeticOperators()
  {
    constexpr vec3_t<float> v1(1.0f, 2.0f, 3.0f);
    constexpr vec3_t<float> v2(4.0f, 5.0f, 6.0f);

    // Addition
    constexpr vec3_t<float> addVecs = v1 + v2;
    KRYS_EXPECT_EQUAL("Addition operator x", addVecs.x, 5.0f);
    KRYS_EXPECT_EQUAL("Addition operator y", addVecs.y, 7.0f);
    KRYS_EXPECT_EQUAL("Addition operator z", addVecs.z, 9.0f);

    constexpr vec3_t<float> addScalar = v1 + 2.0f;
    KRYS_EXPECT_EQUAL("Addition operator (vector + scalar) x", addScalar.x, 3.0f);
    KRYS_EXPECT_EQUAL("Addition operator (vector + scalar) y", addScalar.y, 4.0f);
    KRYS_EXPECT_EQUAL("Addition operator (vector + scalar) z", addScalar.z, 5.0f);

    // Subtraction
    constexpr vec3_t<float> subVecs = v1 - v2;
    KRYS_EXPECT_EQUAL("Subtraction operator x", subVecs.x, -3.0f);
    KRYS_EXPECT_EQUAL("Subtraction operator y", subVecs.y, -3.0f);
    KRYS_EXPECT_EQUAL("Subtraction operator z", subVecs.z, -3.0f);

    constexpr vec3_t<float> subScalar = v1 - 1.0f;
    KRYS_EXPECT_EQUAL("Subtraction operator (vector - scalar) x", subScalar.x, 0.0f);
    KRYS_EXPECT_EQUAL("Subtraction operator (vector - scalar) y", subScalar.y, 1.0f);
    KRYS_EXPECT_EQUAL("Subtraction operator (vector - scalar) z", subScalar.z, 2.0f);

    // Multiplication
    constexpr vec3_t<float> mulVecs = v1 * v2;
    KRYS_EXPECT_EQUAL("Multiplication operator x", mulVecs.x, 4.0f);
    KRYS_EXPECT_EQUAL("Multiplication operator y", mulVecs.y, 10.0f);
    KRYS_EXPECT_EQUAL("Multiplication operator z", mulVecs.z, 18.0f);

    constexpr vec3_t<float> mulScalar = v1 * 2.0f;
    KRYS_EXPECT_EQUAL("Multiplication operator (vector * scalar) x", mulScalar.x, 2.0f);
    KRYS_EXPECT_EQUAL("Multiplication operator (vector * scalar) y", mulScalar.y, 4.0f);
    KRYS_EXPECT_EQUAL("Multiplication operator (vector * scalar) z", mulScalar.z, 6.0f);

    // Division
    constexpr vec3_t<float> divVecs = v2 / v1;
    KRYS_EXPECT_EQUAL("Division operator x", divVecs.x, 4.0f);
    KRYS_EXPECT_EQUAL("Division operator y", divVecs.y, 2.5f);
    KRYS_EXPECT_EQUAL("Division operator z", divVecs.z, 2.0f);

    constexpr vec3_t<float> divScalar = v2 / 2.0f;
    KRYS_EXPECT_EQUAL("Division operator (vector / scalar) x", divScalar.x, 2.0f);
    KRYS_EXPECT_EQUAL("Division operator (vector / scalar) y", divScalar.y, 2.5f);
    KRYS_EXPECT_EQUAL("Division operator (vector / scalar) z", divScalar.z, 3.0f);
  }

  constexpr void Test_UnaryOperator()
  {
    constexpr vec3_t<float> v(1.0f, -2.0f, 3.0f);
    constexpr vec3_t<float> negative = -v;
    KRYS_EXPECT_EQUAL("Unary minus operator x", negative.x, -1.0f);
    KRYS_EXPECT_EQUAL("Unary minus operator y", negative.y, 2.0f);
    KRYS_EXPECT_EQUAL("Unary minus operator z", negative.z, -3.0f);
  }
}
