#include "MTL/Matrices/Mat4x4.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Mat4x4()
  {
    // Construction
    constexpr mat4x4_t<float> identity = mat4x4_t<float>::I();
    KRYS_EXPECT_EQUAL("Identity Matrix Construction", identity,
                      (mat4x4_t<float>(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f)));

    constexpr mat4x4_t<float> scalar(2.0f);
    KRYS_EXPECT_EQUAL("Scalar Matrix Construction", scalar,
                      (mat4x4_t<float>(2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 2.0f)));

    constexpr mat4x4_t<float> components(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f,
                                         12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    KRYS_EXPECT_EQUAL("Component-wise Matrix Construction", components,
                      (mat4x4_t<float>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f,
                                       12.0f, 13.0f, 14.0f, 15.0f, 16.0f)));

    // Copy Construction
    constexpr mat4x4_t<float> copy(components);
    KRYS_EXPECT_EQUAL("Copy Constructor", copy, components);

    // Move Construction
    constexpr mat4x4_t<float> temp_move(components);
    constexpr mat4x4_t<float> move(std::move(temp_move));
    KRYS_EXPECT_EQUAL("Move Constructor", move, components);

    // Equality
    constexpr mat4x4_t<float> unequal(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f,
                                      13.0f, 14.0f, 15.0f, 16.0f, 17.0f);
    KRYS_EXPECT_TRUE("Equality Comparison (Equal)", components == copy);
    KRYS_EXPECT_FALSE("Equality Comparison (Not Equal)", components == unequal);
    KRYS_EXPECT_TRUE("Inequality Comparison (Not Equal)", components != unequal);

    // Addition
    constexpr mat4x4_t<float> sum = components + scalar;
    KRYS_EXPECT_EQUAL("Matrix Addition", sum,
                      (mat4x4_t<float>(3.0f, 2.0f, 3.0f, 4.0f, 5.0f, 8.0f, 7.0f, 8.0f, 9.0f, 10.0f, 13.0f,
                                       12.0f, 13.0f, 14.0f, 15.0f, 18.0f)));

    // Subtraction
    constexpr mat4x4_t<float> diff = components - scalar;
    KRYS_EXPECT_EQUAL("Matrix Subtraction", diff,
                      (mat4x4_t<float>(-1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 4.0f, 7.0f, 8.0f, 9.0f, 10.0f, 9.0f,
                                       12.0f, 13.0f, 14.0f, 15.0f, 14.0f)));

    // Multiplication
    constexpr mat4x4_t<float> product = components * 2.0f;
    KRYS_EXPECT_EQUAL("Matrix Scalar Multiplication", product,
                      (mat4x4_t<float>(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f,
                                       22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f)));

    constexpr mat4x4_t<float> mat_product = components * identity;
    KRYS_EXPECT_EQUAL("Matrix Multiplication with Identity", mat_product, components);

    // Division
    constexpr mat4x4_t<float> quotient = components / 2.0f;
    KRYS_EXPECT_EQUAL("Matrix Scalar Division", quotient,
                      (mat4x4_t<float>(0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f,
                                       6.5f, 7.0f, 7.5f, 8.0f)));

    // Negation
    constexpr mat4x4_t<float> negated = -components;
    KRYS_EXPECT_EQUAL("Matrix Negation", negated,
                      (mat4x4_t<float>(-1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f, -9.0f, -10.0f,
                                       -11.0f, -12.0f, -13.0f, -14.0f, -15.0f, -16.0f)));

    // Element Access
    constexpr auto col0 = components[0];
    constexpr auto col1 = components[1];
    constexpr auto col2 = components[2];
    constexpr auto col3 = components[3];
    KRYS_EXPECT_EQUAL("Element Access (Column 0)", col0, (mat4x4_t<float>::column_t(1.0f, 2.0f, 3.0f, 4.0f)));
    KRYS_EXPECT_EQUAL("Element Access (Column 1)", col1, (mat4x4_t<float>::column_t(5.0f, 6.0f, 7.0f, 8.0f)));
    KRYS_EXPECT_EQUAL("Element Access (Column 2)", col2,
                      (mat4x4_t<float>::column_t(9.0f, 10.0f, 11.0f, 12.0f)));
    KRYS_EXPECT_EQUAL("Element Access (Column 3)", col3,
                      (mat4x4_t<float>::column_t(13.0f, 14.0f, 15.0f, 16.0f)));
  }
}
