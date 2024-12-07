#include "MTL/Matrices/Ext/Clamp.hpp"
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

  static void Test_Mat2x2_Clamp()
  {
    using mat_t = Mat2x2;
    constexpr mat_t mat {1, 2, 3, 4};

    constexpr mat_t matMin {1, 3, 7, 4};
    constexpr mat_t matMax {2, 4, 8, 4};
    KRYS_EXPECT_EQUAL("Clamp Mat2x2-Mat2x2", Clamp(mat, matMin, matMax), mat_t(1, 3, 7, 4));
    KRYS_EXPECT_EQUAL("Clamp Mat2x2-Scalar", Clamp(mat, 4.0f, 7.0f), mat_t(4, 4, 4, 4));
  }

  static void Test_Mat2x3_Clamp()
  {
    using mat_t = Mat2x3;
    constexpr mat_t mat {1, 2, 3, 4, 5, 6};

    constexpr mat_t matMin {1, 3, 7, 4, 6, 6};
    constexpr mat_t matMax {2, 4, 8, 4, 7, 7};
    KRYS_EXPECT_EQUAL("Clamp Mat2x3-Mat2x3", Clamp(mat, matMin, matMax), mat_t(1, 3, 7, 4, 6, 6));
    KRYS_EXPECT_EQUAL("Clamp Mat2x3-Scalar", Clamp(mat, 4.0f, 7.0f), mat_t(4, 4, 4, 4, 5, 6));
  }

  static void Test_Mat2x4_Clamp()
  {
    using mat_t = Mat2x4;
    constexpr mat_t mat {1, 2, 3, 4, 5, 6, 7, 8};

    constexpr mat_t matMin {1, 3, 3, 5, 6, 6, 7, 7};
    constexpr mat_t matMax {2, 4, 4, 6, 7, 8, 8, 9};
    KRYS_EXPECT_EQUAL("Clamp Mat2x4-Mat2x4", Clamp(mat, matMin, matMax), mat_t(1, 3, 3, 5, 6, 6, 7, 8));
    KRYS_EXPECT_EQUAL("Clamp Mat2x4-Scalar", Clamp(mat, 4.0f, 7.0f), mat_t(4, 4, 4, 4, 5, 6, 7, 7));
  }

  static void Test_Mat3x2_Clamp()
  {
    using mat_t = Mat3x2;
    constexpr mat_t mat {1, 2, 3, 4, 5, 6};

    constexpr mat_t matMin {1, 3, 3, 5, 6, 6};
    constexpr mat_t matMax {2, 4, 4, 6, 7, 8};
    KRYS_EXPECT_EQUAL("Clamp Mat3x2-Mat3x2", Clamp(mat, matMin, matMax), mat_t(1, 3, 3, 5, 6, 6));
    KRYS_EXPECT_EQUAL("Clamp Mat3x2-Scalar", Clamp(mat, 4.0f, 7.0f), mat_t(4, 4, 4, 4, 5, 6));
  }

  static void Test_Mat3x3_Clamp()
  {
    using mat_t = Mat3x3;
    constexpr mat_t mat {1, 2, 3, 4, 5, 6, 7, 8, 9};

    constexpr mat_t matMin {1, 3, 3, 5, 6, 6, 8, 8, 8};
    constexpr mat_t matMax {2, 4, 4, 6, 7, 8, 9, 9, 9};
    KRYS_EXPECT_EQUAL("Clamp Mat3x3-Mat3x3", Clamp(mat, matMin, matMax), mat_t(1, 3, 3, 5, 6, 6, 8, 8, 9));
    KRYS_EXPECT_EQUAL("Clamp Mat3x3-Scalar", Clamp(mat, 4.0f, 7.0f), mat_t(4, 4, 4, 4, 5, 6, 7, 7, 7));
  }

  static void Test_Mat3x4_Clamp()
  {
    using mat_t = Mat3x4;
    constexpr mat_t mat {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    constexpr mat_t matMin {1, 3, 3, 5, 6, 6, 8, 8, 10, 10, 11, 11};
    constexpr mat_t matMax {2, 4, 4, 6, 7, 8, 9, 9, 11, 11, 12, 12};
    KRYS_EXPECT_EQUAL("Clamp Mat3x4-Mat3x4", Clamp(mat, matMin, matMax),
                      mat_t(1, 3, 3, 5, 6, 6, 8, 8, 10, 10, 11, 12));
    KRYS_EXPECT_EQUAL("Clamp Mat3x4-Scalar", Clamp(mat, 4.0f, 7.0f),
                      mat_t(4, 4, 4, 4, 5, 6, 7, 7, 7, 7, 7, 7));
  }

  static void Test_Mat4x2_Clamp()
  {
    using mat_t = Mat4x2;
    constexpr mat_t mat {1, 2, 3, 4, 5, 6, 7, 8};

    constexpr mat_t matMin {1, 3, 3, 5, 6, 6, 7, 7};
    constexpr mat_t matMax {2, 4, 4, 6, 7, 8, 8, 9};
    KRYS_EXPECT_EQUAL("Clamp Mat4x2-Mat4x2", Clamp(mat, matMin, matMax), mat_t(1, 3, 3, 5, 6, 6, 7, 8));
    KRYS_EXPECT_EQUAL("Clamp Mat4x2-Scalar", Clamp(mat, 4.0f, 7.0f), mat_t(4, 4, 4, 4, 5, 6, 7, 7));
  }

  static void Test_Mat4x3_Clamp()
  {
    using mat_t = Mat4x3;
    constexpr mat_t mat {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    constexpr mat_t matMin {1, 3, 3, 5, 6, 6, 8, 8, 9, 10, 10, 11};
    constexpr mat_t matMax {2, 4, 4, 6, 7, 8, 9, 9, 10, 11, 12, 12};
    KRYS_EXPECT_EQUAL("Clamp Mat4x3-Mat4x3", Clamp(mat, matMin, matMax),
                      mat_t(1, 3, 3, 5, 6, 6, 8, 8, 9, 10, 11, 12));
    KRYS_EXPECT_EQUAL("Clamp Mat4x3-Scalar", Clamp(mat, 4.0f, 7.0f),
                      mat_t(4, 4, 4, 4, 5, 6, 7, 7, 7, 7, 7, 7));
  }

  static void Test_Mat4x4_Clamp()
  {
    using mat_t = Mat4x4;
    constexpr mat_t mat {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    constexpr mat_t matMin {1, 3, 3, 5, 6, 6, 8, 8, 9, 10, 10, 11, 13, 13, 14, 14};
    constexpr mat_t matMax {2, 4, 4, 6, 7, 8, 9, 9, 10, 11, 12, 12, 14, 15, 15, 16};
    KRYS_EXPECT_EQUAL("Clamp Mat4x4-Mat4x4", Clamp(mat, matMin, matMax),
                      mat_t(1, 3, 3, 5, 6, 6, 8, 8, 9, 10, 11, 12, 13, 14, 15, 16));
    KRYS_EXPECT_EQUAL("Clamp Mat4x4-Scalar", Clamp(mat, 4.0f, 7.0f),
                      mat_t(4, 4, 4, 4, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7));
  }
}
