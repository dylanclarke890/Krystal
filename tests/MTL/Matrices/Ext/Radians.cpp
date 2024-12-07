#include "MTL/Matrices/Ext/Radians.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"
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
  constexpr float PI = MTL::Pi<float>();

  static void Test_Mat2x2_Radians()
  {
    using mat_t = Mat2x2;
    constexpr mat_t mat {30, 45, 60, 90};
    KRYS_EXPECT_EQUAL("Radians Mat2x2", Radians(mat), mat_t(PI / 6, PI / 4, PI / 3, PI / 2));
  }

  static void Test_Mat2x3_Radians()
  {
    using mat_t = Mat2x3;
    constexpr mat_t mat {30, 45, 60, 90, 180, 360};
    KRYS_EXPECT_EQUAL("Radians Mat2x3", Radians(mat), mat_t(PI / 6, PI / 4, PI / 3, PI / 2, PI, PI * 2));
  }

  static void Test_Mat2x4_Radians()
  {
    using mat_t = Mat2x4;
    constexpr mat_t mat {30, 45, 60, 90, 180, 360, 120, 60};
    KRYS_EXPECT_EQUAL("Radians Mat2x4", Radians(mat),
                      mat_t(PI / 6, PI / 4, PI / 3, PI / 2, PI, PI * 2, PI * (2.0f / 3.0f), PI / 3));
  }

  static void Test_Mat3x2_Radians()
  {
    using mat_t = Mat3x2;
    constexpr mat_t mat {30, 45, 60, 90, 180, 360};
    KRYS_EXPECT_EQUAL("Radians Mat3x2", Radians(mat), mat_t(PI / 6, PI / 4, PI / 3, PI / 2, PI, PI * 2));
  }

  static void Test_Mat3x3_Radians()
  {
    using mat_t = Mat3x3;
    constexpr mat_t mat {0, 180, -90, 45, -60, 360, -30, 135, 22.5f};
    KRYS_EXPECT_EQUAL("Radians Mat3x3", Radians(mat),
                      mat_t(0, PI, -PI / 2, PI / 4, -PI / 3, 2 * PI, -PI / 6, 3 * PI / 4, PI / 8));
  }

  static void Test_Mat3x4_Radians()
  {
    using mat_t = Mat3x4;
    constexpr mat_t mat {0, 180, -90, 45, -60, 360, -30, 135, 22.5f, 0, 180, -90};
    KRYS_EXPECT_EQUAL(
      "Radians Mat3x4", Radians(mat),
      mat_t(0, PI, -PI / 2, PI / 4, -PI / 3, 2 * PI, -PI / 6, 3 * PI / 4, PI / 8, 0, PI, -PI / 2));
  }

  static void Test_Mat4x2_Radians()
  {
    using mat_t = Mat4x2;
    constexpr mat_t mat {30, 45, 60, 90, 180, 360, 120, 60};
    KRYS_EXPECT_EQUAL("Radians Mat4x2", Radians(mat),
                      mat_t(PI / 6, PI / 4, PI / 3, PI / 2, PI, PI * 2, PI * (2.0f / 3.0f), PI / 3));
  }

  static void Test_Mat4x3_Radians()
  {
    using mat_t = Mat4x3;
    constexpr mat_t mat {0, 180, -90, 45, -60, 360, -30, 135, 22.5f, 0, 180, -90};
    KRYS_EXPECT_EQUAL(
      "Radians Mat4x3", Radians(mat),
      mat_t(0, PI, -PI / 2, PI / 4, -PI / 3, 2 * PI, -PI / 6, 3 * PI / 4, PI / 8, 0, PI, -PI / 2));
  }

  static void Test_Mat4x4_Radians()
  {
    using mat_t = Mat4x4;
    constexpr mat_t mat {0, 180, -90, 45, -60, 360, -30, 135, 22.5f, 0, 180, -90, 180, 360, 120, 60};
    KRYS_EXPECT_EQUAL("Radians Mat4x4", Radians(mat),
                      mat_t(0, PI, -PI / 2, PI / 4, -PI / 3, 2 * PI, -PI / 6, 3 * PI / 4, PI / 8, 0, PI,
                            -PI / 2, PI, PI * 2, PI * (2.0f / 3.0f), PI / 3));
  }
}
