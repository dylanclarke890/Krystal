#include "MTL/Matrices/Ext/MinMax.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat2x3.hpp"
#include "MTL/Matrices/Mat2x4.hpp"
#include "MTL/Matrices/Mat3x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x2.hpp"
#include "MTL/Matrices/Mat4x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Mat2x2_MinMax()
  {
    using mati_t = mat2x2_t<int>;
    constexpr mati_t mati {1, -2, 3, -4};
    KRYS_EXPECT_EQUAL("Min Mat2x2-Scalar", Min(mati, 1), mati_t(1, -2, 1, -4));
    KRYS_EXPECT_EQUAL("Min Mat2x2-Mat2x2", Min(mati, mati_t(1, 1, 1, 1)), mati_t(1, -2, 1, -4));
    KRYS_EXPECT_EQUAL("Max Mat2x2-Scalar", Max(mati, 1), mati_t(1, 1, 3, 1));
    KRYS_EXPECT_EQUAL("Max Mat2x2-Mat2x2", Max(mati, mati_t(1, 1, 1, 1)), mati_t(1, 1, 3, 1));

    using matf_t = mat2x2_t<float>;
    constexpr matf_t matf {1, -2, 3, -4};
    KRYS_EXPECT_EQUAL("FMin Mat2x2-Scalar", FMin(matf, 1.0f), matf_t(1, -2, 1, -4));
    KRYS_EXPECT_EQUAL("FMin Mat2x2-Mat2x2", FMin(matf, matf_t(1, 1, 1, 1)), matf_t(1, -2, 1, -4));
    KRYS_EXPECT_EQUAL("FMax Mat2x2-Scalar", FMax(matf, 1.0f), matf_t(1, 1, 3, 1));
    KRYS_EXPECT_EQUAL("FMax Mat2x2-Mat2x2", FMax(matf, matf_t(1, 1, 1, 1)), matf_t(1, 1, 3, 1));
  }

  static void Test_Mat2x3_MinMax()
  {
    using mati_t = mat2x3_t<int>;
    constexpr mati_t mati {1, -2, 3, -4, 5, -6};
    KRYS_EXPECT_EQUAL("Min Mat2x3-Scalar", Min(mati, 1), mati_t(1, -2, 1, -4, 1, -6));
    KRYS_EXPECT_EQUAL("Min Mat2x3-Mat2x3", Min(mati, mati_t(1, 1, 1, 1, 1, 1)), mati_t(1, -2, 1, -4, 1, -6));
    KRYS_EXPECT_EQUAL("Max Mat2x3-Scalar", Max(mati, 1), mati_t(1, 1, 3, 1, 5, 1));
    KRYS_EXPECT_EQUAL("Max Mat2x3-Mat2x3", Max(mati, mati_t(1, 1, 1, 1, 1, 1)), mati_t(1, 1, 3, 1, 5, 1));

    using matf_t = mat2x3_t<float>;
    constexpr matf_t matf {1, -2, 3, -4, 5, -6};
    KRYS_EXPECT_EQUAL("FMin Mat2x3-Scalar", FMin(matf, 1.0f), matf_t(1, -2, 1, -4, 1, -6));
    KRYS_EXPECT_EQUAL("FMin Mat2x3-Mat2x3", FMin(matf, matf_t(1, 1, 1, 1, 1, 1)),
                      matf_t(1, -2, 1, -4, 1, -6));
    KRYS_EXPECT_EQUAL("FMax Mat2x3-Scalar", FMax(matf, 1.0f), matf_t(1, 1, 3, 1, 5, 1));
    KRYS_EXPECT_EQUAL("FMax Mat2x3-Mat2x3", FMax(matf, matf_t(1, 1, 1, 1, 1, 1)), matf_t(1, 1, 3, 1, 5, 1));
  }

  static void Test_Mat2x4_MinMax()
  {
    using mati_t = mat2x4_t<int>;
    constexpr mati_t mati {1, -2, 3, -4, 5, -6, 7, -8};
    KRYS_EXPECT_EQUAL("Min Mat2x4-Scalar", Min(mati, 1), mati_t(1, -2, 1, -4, 1, -6, 1, -8));
    KRYS_EXPECT_EQUAL("Min Mat2x4-Mat2x4", Min(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, -2, 1, -4, 1, -6, 1, -8));
    KRYS_EXPECT_EQUAL("Max Mat2x4-Scalar", Max(mati, 1), mati_t(1, 1, 3, 1, 5, 1, 7, 1));
    KRYS_EXPECT_EQUAL("Max Mat2x4-Mat2x4", Max(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, 1, 3, 1, 5, 1, 7, 1));

    using matf_t = mat2x4_t<float>;
    constexpr matf_t matf {1, -2, 3, -4, 5, -6, 7, -8};
    KRYS_EXPECT_EQUAL("FMin Mat2x4-Scalar", FMin(matf, 1.0f), matf_t(1, -2, 1, -4, 1, -6, 1, -8));
    KRYS_EXPECT_EQUAL("FMin Mat2x4-Mat2x4", FMin(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, -2, 1, -4, 1, -6, 1, -8));
    KRYS_EXPECT_EQUAL("FMax Mat2x4-Scalar", FMax(matf, 1.0f), matf_t(1, 1, 3, 1, 5, 1, 7, 1));
    KRYS_EXPECT_EQUAL("FMax Mat2x4-Mat2x4", FMax(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, 1, 3, 1, 5, 1, 7, 1));
  }

  static void Test_Mat3x2_MinMax()
  {
    using mati_t = mat3x2_t<int>;
    constexpr mati_t mati {1, -2, 3, -4, 5, -6};
    KRYS_EXPECT_EQUAL("Min Mat3x2-Scalar", Min(mati, 1), mati_t(1, -2, 1, -4, 1, -6));
    KRYS_EXPECT_EQUAL("Min Mat3x2-Mat3x2", Min(mati, mati_t(1, 1, 1, 1, 1, 1)), mati_t(1, -2, 1, -4, 1, -6));
    KRYS_EXPECT_EQUAL("Max Mat3x2-Scalar", Max(mati, 1), mati_t(1, 1, 3, 1, 5, 1));
    KRYS_EXPECT_EQUAL("Max Mat3x2-Mat3x2", Max(mati, mati_t(1, 1, 1, 1, 1, 1)), mati_t(1, 1, 3, 1, 5, 1));

    using matf_t = mat3x2_t<float>;
    constexpr matf_t matf {1, -2, 3, -4, 5, -6};
    KRYS_EXPECT_EQUAL("FMin Mat3x2-Scalar", FMin(matf, 1.0f), matf_t(1, -2, 1, -4, 1, -6));
    KRYS_EXPECT_EQUAL("FMin Mat3x2-Mat3x2", FMin(matf, matf_t(1, 1, 1, 1, 1, 1)),
                      matf_t(1, -2, 1, -4, 1, -6));
    KRYS_EXPECT_EQUAL("FMax Mat3x2-Scalar", FMax(matf, 1.0f), matf_t(1, 1, 3, 1, 5, 1));
    KRYS_EXPECT_EQUAL("FMax Mat3x2-Mat3x2", FMax(matf, matf_t(1, 1, 1, 1, 1, 1)), matf_t(1, 1, 3, 1, 5, 1));
  }

  static void Test_Mat3x3_MinMax()
  {
    using mati_t = mat3x3_t<int>;
    constexpr mati_t mati {1, -2, 3, -4, 5, -6, 7, -8, 9};
    KRYS_EXPECT_EQUAL("Min Mat3x3-Scalar", Min(mati, 1), mati_t(1, -2, 1, -4, 1, -6, 1, -8, 1));
    KRYS_EXPECT_EQUAL("Min Mat3x3-Mat3x3", Min(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, -2, 1, -4, 1, -6, 1, -8, 1));
    KRYS_EXPECT_EQUAL("Max Mat3x3-Scalar", Max(mati, 1), mati_t(1, 1, 3, 1, 5, 1, 7, 1, 9));
    KRYS_EXPECT_EQUAL("Max Mat3x3-Mat3x3", Max(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, 1, 3, 1, 5, 1, 7, 1, 9));

    using matf_t = mat3x3_t<float>;
    constexpr matf_t matf {1, -2, 3, -4, 5, -6, 7, -8, 9};
    KRYS_EXPECT_EQUAL("FMin Mat3x3-Scalar", FMin(matf, 1.0f), matf_t(1, -2, 1, -4, 1, -6, 1, -8, 1));
    KRYS_EXPECT_EQUAL("FMin Mat3x3-Mat3x3", FMin(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, -2, 1, -4, 1, -6, 1, -8, 1));
    KRYS_EXPECT_EQUAL("FMax Mat3x3-Scalar", FMax(matf, 1.0f), matf_t(1, 1, 3, 1, 5, 1, 7, 1, 9));
    KRYS_EXPECT_EQUAL("FMax Mat3x3-Mat3x3", FMax(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, 1, 3, 1, 5, 1, 7, 1, 9));
  }

  static void Test_Mat3x4_MinMax()
  {
    using mati_t = mat3x4_t<int>;
    constexpr mati_t mati {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12};
    KRYS_EXPECT_EQUAL("Min Mat3x4-Scalar", Min(mati, 1), mati_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12));
    KRYS_EXPECT_EQUAL("Min Mat3x4-Mat3x4", Min(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12));
    KRYS_EXPECT_EQUAL("Max Mat3x4-Scalar", Max(mati, 1), mati_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1));
    KRYS_EXPECT_EQUAL("Max Mat3x4-Mat3x4", Max(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1));

    using matf_t = mat3x4_t<float>;
    constexpr matf_t matf {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12};
    KRYS_EXPECT_EQUAL("FMin Mat3x4-Scalar", FMin(matf, 1.0f),
                      matf_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12));
    KRYS_EXPECT_EQUAL("FMin Mat3x4-Mat3x4", FMin(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12));
    KRYS_EXPECT_EQUAL("FMax Mat3x4-Scalar", FMax(matf, 1.0f), matf_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1));
    KRYS_EXPECT_EQUAL("FMax Mat3x4-Mat3x4", FMax(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1));
  }

  static void Test_Mat4x2_MinMax()
  {
    using mati_t = mat4x2_t<int>;
    constexpr mati_t mati {1, -2, 3, -4, 5, -6, 7, -8};
    KRYS_EXPECT_EQUAL("Min Mat4x2-Scalar", Min(mati, 1), mati_t(1, -2, 1, -4, 1, -6, 1, -8));
    KRYS_EXPECT_EQUAL("Min Mat4x2-Mat4x2", Min(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, -2, 1, -4, 1, -6, 1, -8));
    KRYS_EXPECT_EQUAL("Max Mat4x2-Scalar", Max(mati, 1), mati_t(1, 1, 3, 1, 5, 1, 7, 1));
    KRYS_EXPECT_EQUAL("Max Mat4x2-Mat4x2", Max(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, 1, 3, 1, 5, 1, 7, 1));

    using matf_t = mat4x2_t<float>;
    constexpr matf_t matf {1, -2, 3, -4, 5, -6, 7, -8};
    KRYS_EXPECT_EQUAL("FMin Mat4x2-Scalar", FMin(matf, 1.0f), matf_t(1, -2, 1, -4, 1, -6, 1, -8));
    KRYS_EXPECT_EQUAL("FMin Mat4x2-Mat4x2", FMin(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, -2, 1, -4, 1, -6, 1, -8));
    KRYS_EXPECT_EQUAL("FMax Mat4x2-Scalar", FMax(matf, 1.0f), matf_t(1, 1, 3, 1, 5, 1, 7, 1));
    KRYS_EXPECT_EQUAL("FMax Mat4x2-Mat4x2", FMax(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, 1, 3, 1, 5, 1, 7, 1));
  }

  static void Test_Mat4x3_MinMax()
  {
    using mati_t = mat4x3_t<int>;
    constexpr mati_t mati {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12};
    KRYS_EXPECT_EQUAL("Min Mat4x3-Scalar", Min(mati, 1), mati_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12));
    KRYS_EXPECT_EQUAL("Min Mat4x3-Mat4x3", Min(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12));
    KRYS_EXPECT_EQUAL("Max Mat4x3-Scalar", Max(mati, 1), mati_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1));
    KRYS_EXPECT_EQUAL("Max Mat4x3-Mat4x3", Max(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1));

    using matf_t = mat4x3_t<float>;
    constexpr matf_t matf {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12};
    KRYS_EXPECT_EQUAL("FMin Mat4x3-Scalar", FMin(matf, 1.0f),
                      matf_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12));
    KRYS_EXPECT_EQUAL("FMin Mat4x3-Mat4x3", FMin(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12));
    KRYS_EXPECT_EQUAL("FMax Mat4x3-Scalar", FMax(matf, 1.0f), matf_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1));
    KRYS_EXPECT_EQUAL("FMax Mat4x3-Mat4x3", FMax(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1));
  }

  static void Test_Mat4x4_MinMax()
  {
    using mati_t = mat4x4_t<int>;
    constexpr mati_t mati {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16};
    KRYS_EXPECT_EQUAL("Min Mat4x4-Scalar", Min(mati, 1),
                      mati_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12, 1, -14, 1, -16));
    KRYS_EXPECT_EQUAL("Min Mat4x4-Mat4x4", Min(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12, 1, -14, 1, -16));
    KRYS_EXPECT_EQUAL("Max Mat4x4-Scalar", Max(mati, 1),
                      mati_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1, 13, 1, 15, 1));
    KRYS_EXPECT_EQUAL("Max Mat4x4-Mat4x4", Max(mati, mati_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      mati_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1, 13, 1, 15, 1));

    using matf_t = mat4x4_t<float>;
    constexpr matf_t matf {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16};
    KRYS_EXPECT_EQUAL("FMin Mat4x4-Scalar", FMin(matf, 1.0f),
                      matf_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12, 1, -14, 1, -16));
    KRYS_EXPECT_EQUAL("FMin Mat4x4-Mat4x4",
                      FMin(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, -2, 1, -4, 1, -6, 1, -8, 1, -10, 1, -12, 1, -14, 1, -16));
    KRYS_EXPECT_EQUAL("FMax Mat4x4-Scalar", FMax(matf, 1.0f),
                      matf_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1, 13, 1, 15, 1));
    KRYS_EXPECT_EQUAL("FMax Mat4x4-Mat4x4",
                      FMax(matf, matf_t(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)),
                      matf_t(1, 1, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1, 13, 1, 15, 1));
  }
}
