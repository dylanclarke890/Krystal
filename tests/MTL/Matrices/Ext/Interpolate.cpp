#include "MTL/Matrices/Ext/Interpolate.hpp"
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

  static void Test_Mat2x2_Lerp()
  {
    using mat_t = Mat2x2;
    constexpr mat_t x {1, 2, 3, 4};
    constexpr mat_t y {5, 6, 7, 8};

    KRYS_EXPECT_EQUAL("Lerp Mat2x2 t=0", Lerp(x, y, 0.0f), x);
    KRYS_EXPECT_EQUAL("Lerp Mat2x2 t=1", Lerp(x, y, 1.0f), y);
    KRYS_EXPECT_EQUAL("Lerp Mat2x2 t=0.5", Lerp(x, y, 0.5f), mat_t(3, 4, 5, 6));

    constexpr mat_t t {0.0f, 0.5f, 1.0f, 0.25f};
    KRYS_EXPECT_EQUAL("Lerp Mat2x2 VecT", Lerp(x, y, t), mat_t(1, 4, 7, 5));
  }

  static void Test_Mat2x3_Lerp()
  {
    using mat_t = Mat2x3;
    constexpr mat_t x {1, 2, 3, 4, 5, 6};
    constexpr mat_t y {7, 8, 9, 10, 11, 12};

    KRYS_EXPECT_EQUAL("Lerp Mat2x3 t=0", Lerp(x, y, 0.0f), x);
    KRYS_EXPECT_EQUAL("Lerp Mat2x3 t=1", Lerp(x, y, 1.0f), y);
    KRYS_EXPECT_EQUAL("Lerp Mat2x3 t=0.5", Lerp(x, y, 0.5f), mat_t(4, 5, 6, 7, 8, 9));

    constexpr mat_t t {0.5f, 0.25f, 0.75f, 0.0f, 1.0f, 0.5f};
    KRYS_EXPECT_EQUAL("Lerp Mat2x3 VecT", Lerp(x, y, t), mat_t(4, 3.5f, 7.5f, 4, 11, 9));
  }

  static void Test_Mat2x4_Lerp()
  {
    using mat_t = Mat2x4;
    constexpr mat_t x {1, 2, 3, 4, 5, 6, 7, 8};
    constexpr mat_t y {9, 10, 11, 12, 13, 14, 15, 16};

    KRYS_EXPECT_EQUAL("Lerp Mat2x4 t=0", Lerp(x, y, 0.0f), x);
    KRYS_EXPECT_EQUAL("Lerp Mat2x4 t=1", Lerp(x, y, 1.0f), y);
    KRYS_EXPECT_EQUAL("Lerp Mat2x4 t=0.5", Lerp(x, y, 0.5f), mat_t(5, 6, 7, 8, 9, 10, 11, 12));

    constexpr mat_t t {0.0f, 0.25f, 0.5f, 0.75f, 1.0f, 0.5f, 0.25f, 0.0f};
    KRYS_EXPECT_EQUAL("Lerp Mat2x4 VecT", Lerp(x, y, t), mat_t(1, 4, 7, 10, 13, 10, 9, 8));
  }

  static void Test_Mat3x2_Lerp()
  {
    using mat_t = Mat3x2;
    constexpr mat_t x {1, 2, 3, 4, 5, 6};
    constexpr mat_t y {7, 8, 9, 10, 11, 12};

    KRYS_EXPECT_EQUAL("Lerp Mat3x2 t=0", Lerp(x, y, 0.0f), x);
    KRYS_EXPECT_EQUAL("Lerp Mat3x2 t=1", Lerp(x, y, 1.0f), y);
    KRYS_EXPECT_EQUAL("Lerp Mat3x2 t=0.5", Lerp(x, y, 0.5f), mat_t(4, 5, 6, 7, 8, 9));

    constexpr mat_t t {0.25f, 0.5f, 0.75f, 0.0f, 1.0f, 0.5f};
    KRYS_EXPECT_EQUAL("Lerp Mat3x2 VecT", Lerp(x, y, t), mat_t(2.5f, 5, 7.5f, 4, 11, 9));
  }

  static void Test_Mat3x3_Lerp()
  {
    using mat_t = Mat3x3;
    constexpr mat_t x {1, 2, 3, 4, 5, 6, 7, 8, 9};
    constexpr mat_t y {10, 11, 12, 13, 14, 15, 16, 17, 18};

    KRYS_EXPECT_EQUAL("Lerp Mat3x3 t=0", Lerp(x, y, 0.0f), x);
    KRYS_EXPECT_EQUAL("Lerp Mat3x3 t=1", Lerp(x, y, 1.0f), y);
    KRYS_EXPECT_EQUAL("Lerp Mat3x3 t=0.5", Lerp(x, y, 0.5f),
                      mat_t(5.5f, 6.5f, 7.5f, 8.5f, 9.5f, 10.5f, 11.5f, 12.5f, 13.5f));

    constexpr mat_t t {{0.5f}, {0.5f}, {0.5f}};
    KRYS_EXPECT_EQUAL("Lerp Mat3x3 VecT", Lerp(mat_t({0}, {0}, {0}), mat_t({1}, {1}, {1}), t), t);
  }

  static void Test_Mat3x4_Lerp()
  {
    using mat_t = Mat3x4;
    constexpr mat_t x {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    constexpr mat_t y {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

    KRYS_EXPECT_EQUAL("Lerp Mat3x4 t=0", Lerp(x, y, 0.0f), x);
    KRYS_EXPECT_EQUAL("Lerp Mat3x4 t=1", Lerp(x, y, 1.0f), y);
    KRYS_EXPECT_EQUAL("Lerp Mat3x4 t=0.5", Lerp(x, y, 0.5f),
                      mat_t(7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18));

    constexpr mat_t t {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 0.5f, 0.25f};
    KRYS_EXPECT_EQUAL("Lerp Mat3x4 VecT", Lerp(x, y, t),
                      mat_t(2.2f, 4.4f, 6.6f, 8.8f, 11, 13.2f, 15.400001f, 17.6f, 19.8f, 22, 17, 15));
  }

  static void Test_Mat4x2_Lerp()
  {
    using mat_t = Mat4x2;
    constexpr mat_t x {1, 2, 3, 4, 5, 6, 7, 8};
    constexpr mat_t y {9, 10, 11, 12, 13, 14, 15, 16};

    KRYS_EXPECT_EQUAL("Lerp Mat4x2 t=0", Lerp(x, y, 0.0f), x);
    KRYS_EXPECT_EQUAL("Lerp Mat4x2 t=1", Lerp(x, y, 1.0f), y);
    KRYS_EXPECT_EQUAL("Lerp Mat4x2 t=0.5", Lerp(x, y, 0.5f), mat_t(5, 6, 7, 8, 9, 10, 11, 12));

    constexpr mat_t t {0.0f, 0.5f, 1.0f, 0.25f, 0.75f, 0.5f, 0.25f, 1.0f};
    KRYS_EXPECT_EQUAL("Lerp Mat4x2 VecT", Lerp(x, y, t), mat_t(1, 6, 11, 6, 11, 10, 9, 16));
  }

  static void Test_Mat4x3_Lerp()
  {
    using mat_t = Mat4x3;
    constexpr mat_t x {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    constexpr mat_t y {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

    KRYS_EXPECT_EQUAL("Lerp Mat4x3 t=0", Lerp(x, y, 0.0f), x);
    KRYS_EXPECT_EQUAL("Lerp Mat4x3 t=1", Lerp(x, y, 1.0f), y);
    KRYS_EXPECT_EQUAL("Lerp Mat4x3 t=0.5", Lerp(x, y, 0.5f),
                      mat_t(7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18));

    constexpr mat_t t {0.5f, 0.25f, 0.75f, 0.0f, 1.0f, 0.5f, 0.75f, 0.5f, 0.25f, 1.0f, 0.0f, 0.5f};
    KRYS_EXPECT_EQUAL("Lerp Mat4x3 VecT", Lerp(x, y, t), mat_t(7, 5, 12, 4, 17, 12, 16, 14, 12, 22, 11, 18));
  }

  static void Test_Mat4x4_Lerp()
  {
    using mat_t = Mat4x4;
    constexpr mat_t x {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    constexpr mat_t y {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

    KRYS_EXPECT_EQUAL("Lerp Mat4x4 t=0", Lerp(x, y, 0.0f), x);
    KRYS_EXPECT_EQUAL("Lerp Mat4x4 t=1", Lerp(x, y, 1.0f), y);
    KRYS_EXPECT_EQUAL("Lerp Mat4x4 t=0.5", Lerp(x, y, 0.5f),
                      mat_t(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24));

    constexpr mat_t t {0.5f, 0.25f, 0.75f, 0.0f,  1.0f,  0.5f, 0.25f, 0.75f,
                       0.0f, 1.0f,  0.5f,  0.25f, 0.75f, 0.0f, 1.0f,  0.5f};
    KRYS_EXPECT_EQUAL("Lerp Mat4x4 VecT", Lerp(x, y, t),
                      mat_t(9, 6.0f, 15, 4, 21, 14, 11, 20, 9, 26, 19, 16, 25, 14, 31, 24));
  }
}
