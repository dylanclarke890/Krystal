#include "MTL/Matrices/Ext/MinMax.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Min()
  {
    // mat2x2
    constexpr mat2x2_t<int> v1 {1, -2, 3, -4};
    constexpr int scalar1 = 1;
    KRYS_EXPECT_EQUAL("Min Mat2x2", Min(v1, scalar1), (mat2x2_t<int> {1, -2, 1, -4}));

    // mat3x3
    constexpr mat3x3_t<int> v2 {1, -1, 0, 5, -5, 10, 4, 3, -3};
    constexpr int scalar2 = -3;
    KRYS_EXPECT_EQUAL("Min Mat3x3", Min(v2, scalar2), (mat3x3_t<int> {-3, -3, -3, -3, -5, -3, -3, -3, -3}));

    // mat4x4
    constexpr mat4x4_t<int> v3 {10, 20, 30, 40, -5, -15, -25, -35, 0, 5, 15, 25, -10, -20, -30, -40};
    constexpr int scalar3 = -10;
    KRYS_EXPECT_EQUAL(
      "Min Mat4x4", Min(v3, scalar3),
      (mat4x4_t<int> {-10, -10, -10, -10, -10, -15, -25, -35, -10, -10, -10, -10, -10, -20, -30, -40}));
  }

  static void Test_FMin()
  {
    // mat2x2
    constexpr mat2x2_t<float> v1 {1.0f, -2.0f, 3.0f, -4.0f};
    constexpr mat2x2_t<float> v2 {0.0f, 0.0f, 2.0f, 2.0f};
    KRYS_EXPECT_EQUAL("FMin Mat2x2", FMin(v1, v2), (mat2x2_t<float> {0.0f, -2.0f, 2.0f, -4.0f}));

    // mat3x3
    constexpr mat3x3_t<float> v3 {1.0f, -1.0f, 0.0f, 5.0f, -5.0f, 10.0f, 4.0f, 3.0f, -3.0f};
    constexpr mat3x3_t<float> v4 {2.0f, -2.0f, 1.0f, 0.0f, -10.0f, 5.0f, 5.0f, 0.0f, -1.0f};
    KRYS_EXPECT_EQUAL("FMin Mat3x3", FMin(v3, v4),
                      (mat3x3_t<float> {1.0f, -2.0f, 0.0f, 0.0f, -10.0f, 5.0f, 4.0f, 0.0f, -3.0f}));

    // mat4x4
    constexpr mat4x4_t<float> v5 {10.0f, 20.0f, 30.0f, 40.0f, -5.0f,  -15.0f, -25.0f, -35.0f,
                                  0.0f,  5.0f,  15.0f, 25.0f, -10.0f, -20.0f, -30.0f, -40.0f};
    constexpr mat4x4_t<float> v6 {15.0f, 10.0f, 35.0f, 20.0f, -10.0f, -10.0f, -30.0f, -40.0f,
                                  10.0f, 0.0f,  20.0f, 15.0f, -5.0f,  -15.0f, -35.0f, -45.0f};
    KRYS_EXPECT_EQUAL("FMin Mat4x4", FMin(v5, v6),
                      (mat4x4_t<float> {10.0f, 10.0f, 30.0f, 20.0f, -10.0f, -15.0f, -30.0f, -40.0f, 0.0f,
                                        0.0f, 15.0f, 15.0f, -10.0f, -20.0f, -35.0f, -45.0f}));
  }

  static void Test_Max()
  {
    // mat2x2
    constexpr mat2x2_t<int> v1 {1, -2, 3, -4};
    constexpr int scalar1 = 0;
    KRYS_EXPECT_EQUAL("Max Mat2x2", Max(v1, scalar1), (mat2x2_t<int> {1, 0, 3, 0}));

    // mat3x3
    constexpr mat3x3_t<int> v2 {1, -1, 0, 5, -5, 10, 4, 3, -3};
    constexpr int scalar2 = 5;
    KRYS_EXPECT_EQUAL("Max Mat3x3", Max(v2, scalar2), (mat3x3_t<int> {5, 5, 5, 5, 5, 10, 5, 5, 5}));

    // mat4x4
    constexpr mat4x4_t<int> v3 {10, 20, 30, 40, -5, -15, -25, -35, 0, 5, 15, 25, -10, -20, -30, -40};
    constexpr int scalar3 = 25;
    KRYS_EXPECT_EQUAL("Max Mat4x4", Max(v3, scalar3),
                      (mat4x4_t<int> {25, 25, 30, 40, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25}));
  }

  static void Test_FMax()
  {
    // mat2x2
    constexpr mat2x2_t<float> v1 {1.0f, -2.0f, 3.0f, -4.0f};
    constexpr mat2x2_t<float> v2 {0.0f, 0.0f, 2.0f, 2.0f};
    KRYS_EXPECT_EQUAL("FMax Mat2x2", FMax(v1, v2), (mat2x2_t<float> {1.0f, 0.0f, 3.0f, 2.0f}));

    // mat3x3
    constexpr mat3x3_t<float> v3 {1.0f, -1.0f, 0.0f, 5.0f, -5.0f, 10.0f, 4.0f, 3.0f, -3.0f};
    constexpr mat3x3_t<float> v4 {2.0f, -2.0f, 1.0f, 0.0f, -10.0f, 5.0f, 5.0f, 0.0f, -1.0f};
    KRYS_EXPECT_EQUAL("FMax Mat3x3", FMax(v3, v4),
                      (mat3x3_t<float> {2.0f, -1.0f, 1.0f, 5.0f, -5.0f, 10.0f, 5.0f, 3.0f, -1.0f}));

    // mat4x4
    constexpr mat4x4_t<float> v5 {10.0f, 20.0f, 30.0f, 40.0f, -5.0f,  -15.0f, -25.0f, -35.0f,
                                  0.0f,  5.0f,  15.0f, 25.0f, -10.0f, -20.0f, -30.0f, -40.0f};
    constexpr mat4x4_t<float> v6 {15.0f, 10.0f, 35.0f, 20.0f, -10.0f, -10.0f, -30.0f, -40.0f,
                                  10.0f, 0.0f,  20.0f, 15.0f, -5.0f,  -15.0f, -35.0f, -45.0f};
    KRYS_EXPECT_EQUAL("FMax Mat4x4", FMax(v5, v6),
                      (mat4x4_t<float> {15.0f, 20.0f, 35.0f, 40.0f, -5.0f, -10.0f, -25.0f, -35.0f, 10.0f,
                                        5.0f, 20.0f, 25.0f, -5.0f, -15.0f, -30.0f, -40.0f}));
  }

}
