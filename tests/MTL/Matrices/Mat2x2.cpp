#include "MTL/Matrices/Mat2x2.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Mat2x2()
  {
    // Construction
    constexpr mat2x2_t<float> identity = mat2x2_t<float>::I();
    KRYS_EXPECT_EQUAL("Identity Matrix Construction", identity, (mat2x2_t<float>(1.0f, 0.0f, 0.0f, 1.0f)));

    constexpr mat2x2_t<float> scalar(2.0f);
    KRYS_EXPECT_EQUAL("Scalar Matrix Construction", scalar, (mat2x2_t<float>(2.0f, 0.0f, 0.0f, 2.0f)));

    constexpr mat2x2_t<float> components({1.0f, 2.0f}, {3.0f, 4.0f});
    KRYS_EXPECT_EQUAL("Component-wise Matrix Construction", components,
                      (mat2x2_t<float>(1.0f, 2.0f, 3.0f, 4.0f)));

    // Copy Construction
    constexpr mat2x2_t<float> copy(components);
    KRYS_EXPECT_EQUAL("Copy Constructor", copy, components);

    // Move Construction
    constexpr mat2x2_t<float> temp_move(components);
    constexpr mat2x2_t<float> move(std::move(temp_move));
    KRYS_EXPECT_EQUAL("Move Constructor", move, components);

    // Equality
    constexpr mat2x2_t<float> unequal(2.0f, 3.0f, 4.0f, 5.0f);
    KRYS_EXPECT_TRUE("Equality Comparison (Equal)", components == copy);
    KRYS_EXPECT_FALSE("Equality Comparison (Not Equal)", components == unequal);
    KRYS_EXPECT_TRUE("Inequality Comparison (Not Equal)", components != unequal);

    // Addition
    constexpr mat2x2_t<float> sum = components + scalar;
    KRYS_EXPECT_EQUAL("Matrix Addition", sum, (mat2x2_t<float>(3.0f, 2.0f, 3.0f, 6.0f)));

    // Subtraction
    constexpr mat2x2_t<float> diff = components - scalar;
    KRYS_EXPECT_EQUAL("Matrix Subtraction", diff, (mat2x2_t<float>(-1.0f, 2.0f, 3.0f, 2.0f)));

    // Multiplication
    constexpr mat2x2_t<float> product = components * scalar;
    KRYS_EXPECT_EQUAL("Matrix Scalar Multiplication", product, (mat2x2_t<float>(2.0f, 4.0f, 6.0f, 8.0f)));

    constexpr mat2x2_t<float> mat_product = components * identity;
    KRYS_EXPECT_EQUAL("Matrix Multiplication with Identity", mat_product, components);

    // Division
    constexpr mat2x2_t<float> quotient = components / 2.0f;
    KRYS_EXPECT_EQUAL("Matrix Scalar Division", quotient, (mat2x2_t<float>(0.5f, 1.0f, 1.5f, 2.0f)));

    // Negation
    constexpr mat2x2_t<float> negated = -components;
    KRYS_EXPECT_EQUAL("Matrix Negation", negated, (mat2x2_t<float>(-1.0f, -2.0f, -3.0f, -4.0f)));

    // Element Access
    constexpr auto col0 = components[0];
    constexpr auto col1 = components[1];
    KRYS_EXPECT_EQUAL("Element Access (Column 0)", col0, (mat2x2_t<float>::column_t(1.0f, 2.0f)));
    KRYS_EXPECT_EQUAL("Element Access (Column 1)", col1, (mat2x2_t<float>::column_t(3.0f, 4.0f)));
  }
}
