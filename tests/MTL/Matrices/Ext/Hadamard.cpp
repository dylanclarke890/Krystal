#include "MTL/Matrices/Ext/Hadamard.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Hadamard()
  {
    // 2x2 matrices
    constexpr mat2x2_t<float> matA2x2 {1.0f, 2.0f, 3.0f, 4.0f};
    constexpr mat2x2_t<float> matB2x2 {5.0f, 6.0f, 7.0f, 8.0f};
    constexpr mat2x2_t<float> expected2x2 {5.0f, 12.0f, 21.0f, 32.0f};
    constexpr auto result2x2 = Hadamard(matA2x2, matB2x2);
    KRYS_EXPECT_EQUAL("Hadamard 2x2", result2x2, expected2x2);

    // 3x3 matrices
    constexpr mat3x3_t<float> matA3x3 {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    constexpr mat3x3_t<float> matB3x3 {9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    constexpr mat3x3_t<float> expected3x3 {9.0f, 16.0f, 21.0f, 24.0f, 25.0f, 24.0f, 21.0f, 16.0f, 9.0f};
    constexpr auto result3x3 = Hadamard(matA3x3, matB3x3);
    KRYS_EXPECT_EQUAL("Hadamard 3x3", result3x3, expected3x3);

    // 4x4 matrices
    constexpr mat4x4_t<float> matA4x4 {1.0f, 2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,
                                       9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    constexpr mat4x4_t<float> matB4x4 {16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f,
                                       8.0f,  7.0f,  6.0f,  5.0f,  4.0f,  3.0f,  2.0f,  1.0f};
    constexpr mat4x4_t<float> expected4x4 {16.0f, 30.0f, 42.0f, 52.0f, 60.0f, 66.0f, 70.0f, 72.0f,
                                           72.0f, 70.0f, 66.0f, 60.0f, 52.0f, 42.0f, 30.0f, 16.0f};
    constexpr auto result4x4 = Hadamard(matA4x4, matB4x4);
    KRYS_EXPECT_EQUAL("Hadamard 4x4", result4x4, expected4x4);
  }
}
