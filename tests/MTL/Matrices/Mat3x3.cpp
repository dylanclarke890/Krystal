#include "MTL/Matrices/Mat3x3.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Mat3x3()
  {
    // Construction
    constexpr mat3x3_t<float> identity = mat3x3_t<float>(1);
    KRYS_EXPECT_EQUAL("Identity Matrix Construction", identity,
                      (mat3x3_t<float>(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f)));

    constexpr mat3x3_t<float> scalar(2.0f);
    KRYS_EXPECT_EQUAL("Scalar Matrix Construction", scalar,
                      (mat3x3_t<float>(2.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 2.0f)));

    constexpr mat3x3_t<float> components(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    KRYS_EXPECT_EQUAL("Component-wise Matrix Construction", components,
                      (mat3x3_t<float>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)));

    // Copy Construction
    constexpr mat3x3_t<float> copy(components);
    KRYS_EXPECT_EQUAL("Copy Constructor", copy, components);

    // Move Construction
    constexpr mat3x3_t<float> temp_move(components);
    constexpr mat3x3_t<float> move(std::move(temp_move));
    KRYS_EXPECT_EQUAL("Move Constructor", move, components);

    // Equality
    constexpr mat3x3_t<float> unequal(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f);
    KRYS_EXPECT_TRUE("Equality Comparison (Equal)", components == copy);
    KRYS_EXPECT_FALSE("Equality Comparison (Not Equal)", components == unequal);
    KRYS_EXPECT_TRUE("Inequality Comparison (Not Equal)", components != unequal);

    // Addition
    constexpr mat3x3_t<float> sum = components + scalar;
    KRYS_EXPECT_EQUAL("Matrix Addition", sum,
                      (mat3x3_t<float>(3.0f, 2.0f, 3.0f, 4.0f, 7.0f, 6.0f, 7.0f, 8.0f, 11.0f)));

    // Subtraction
    constexpr mat3x3_t<float> diff = components - scalar;
    KRYS_EXPECT_EQUAL("Matrix Subtraction", diff,
                      (mat3x3_t<float>(-1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 6.0f, 7.0f, 8.0f, 7.0f)));

    // Multiplication
    constexpr mat3x3_t<float> product = components * 2.0f;
    KRYS_EXPECT_EQUAL("Matrix Scalar Multiplication", product,
                      (mat3x3_t<float>(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f)));

    constexpr mat3x3_t<float> mat_product = components * identity;
    KRYS_EXPECT_EQUAL("Matrix Multiplication with Identity", mat_product, components);

    // Division
    constexpr mat3x3_t<float> quotient = components / 2.0f;
    KRYS_EXPECT_EQUAL("Matrix Scalar Division", quotient,
                      (mat3x3_t<float>(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f)));

    // Negation
    constexpr mat3x3_t<float> negated = -components;
    KRYS_EXPECT_EQUAL("Matrix Negation", negated,
                      (mat3x3_t<float>(-1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f, -9.0f)));

    // Element Access
    constexpr auto col0 = components[0];
    constexpr auto col1 = components[1];
    constexpr auto col2 = components[2];
    KRYS_EXPECT_EQUAL("Element Access (Column 0)", col0, (mat3x3_t<float>::column_t(1.0f, 2.0f, 3.0f)));
    KRYS_EXPECT_EQUAL("Element Access (Column 1)", col1, (mat3x3_t<float>::column_t(4.0f, 5.0f, 6.0f)));
    KRYS_EXPECT_EQUAL("Element Access (Column 2)", col2, (mat3x3_t<float>::column_t(7.0f, 8.0f, 9.0f)));
  }
}
