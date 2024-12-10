#include "MTL/Matrices/Ext/Ranges.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat2x3.hpp"
#include "MTL/Matrices/Mat2x4.hpp"
#include "MTL/Matrices/Mat3x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x2.hpp"
#include "MTL/Matrices/Mat4x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  template <vec_length_t RL, vec_length_t CL>
  constexpr float TestHelper_SumMatrix(const matrix_t<float, RL, CL> &mat)
  {
    float total = 0;
    for (auto it = Begin(mat); it != End(mat); ++it)
      total += *it;
    return total;
  }

  static void Test_Mat2x2_Ranges()
  {
    using mat_t = matrix_t<float, 2, 2>;
    constexpr mat_t mat(1.0f, 2.0f, 3.0f, 4.0f);

    constexpr float sum = TestHelper_SumMatrix(mat);
    KRYS_EXPECT_EQUAL("Ranges Mat2x2", sum, 10.0f);
  }

  static void Test_Mat2x3_Ranges()
  {
    using mat_t = matrix_t<float, 2, 3>;
    constexpr mat_t mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

    constexpr float sum = TestHelper_SumMatrix(mat);
    KRYS_EXPECT_EQUAL("Ranges Mat2x3", sum, 21.0f);
  }

  static void Test_Mat2x4_Ranges()
  {
    using mat_t = matrix_t<float, 2, 4>;
    constexpr mat_t mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

    constexpr float sum = TestHelper_SumMatrix(mat);
    KRYS_EXPECT_EQUAL("Ranges Mat2x4", sum, 36.0f);
  }

  static void Test_Mat3x2_Ranges()
  {
    using mat_t = matrix_t<float, 3, 2>;
    constexpr mat_t mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

    constexpr float sum = TestHelper_SumMatrix(mat);
    KRYS_EXPECT_EQUAL("Ranges Mat3x2", sum, 21.0f);
  }

  static void Test_Mat3x3_Ranges()
  {
    using mat_t = matrix_t<float, 3, 3>;
    constexpr mat_t mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

    constexpr float sum = TestHelper_SumMatrix(mat);
    KRYS_EXPECT_EQUAL("Ranges Mat3x3", sum, 45.0f);
  }

  static void Test_Mat3x4_Ranges()
  {
    using mat_t = matrix_t<float, 3, 4>;
    constexpr mat_t mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f);

    constexpr float sum = TestHelper_SumMatrix(mat);
    KRYS_EXPECT_EQUAL("Ranges Mat3x4", sum, 78.0f);
  }

  static void Test_Mat4x2_Ranges()
  {
    using mat_t = matrix_t<float, 4, 2>;
    constexpr mat_t mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

    constexpr float sum = TestHelper_SumMatrix(mat);
    KRYS_EXPECT_EQUAL("Ranges Mat4x2", sum, 36.0f);
  }

  static void Test_Mat4x3_Ranges()
  {
    using mat_t = matrix_t<float, 4, 3>;
    constexpr mat_t mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f);

    constexpr float sum = TestHelper_SumMatrix(mat);
    KRYS_EXPECT_EQUAL("Ranges Mat4x3", sum, 78.0f);
  }

  static void Test_Mat4x4_Ranges()
  {
    using mat_t = matrix_t<float, 4, 4>;
    constexpr mat_t mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f,
                        14.0f, 15.0f, 16.0f);

    constexpr float sum = TestHelper_SumMatrix(mat);
    KRYS_EXPECT_EQUAL("Ranges Mat4x4", sum, 136.0f);
  }
}
