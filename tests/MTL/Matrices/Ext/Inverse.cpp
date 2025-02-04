#include "MTL/Matrices/Ext/Inverse.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Mat2x2_Inverse()
  {
    using mat_t = Mat2x2;
    constexpr mat_t mat {{4, 2}, {7, 6}};
    KRYS_EXPECT_EQUAL("Inverse Mat2x2", Inverse(mat), mat_t({0.6f, -0.2f}, {-0.7f, 0.4f}));
  }

  static void Test_Mat3x3_Inverse()
  {
    using mat_t = Mat3x3;
    constexpr mat_t mat {{1, -1, 1}, {2, 0, -1}, {-1, 1, 0}};
    KRYS_EXPECT_EQUAL("Inverse Mat3x3", Inverse(mat),
                      mat_t({0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 1.5f}, {1.0f, 0.0f, 1.0f}));
  }

  static void Test_Mat4x4_Inverse()
  {
    using mat_t = Mat4x4;
    constexpr mat_t mat {{1, 0, 0, 0}, {0, 2, 0, 0}, {0, 0, 3, 0}, {0, 0, 0, 4}};
    KRYS_EXPECT_EQUAL("Inverse Mat4x4", Inverse(mat),
                      mat_t({1, 0, 0, 0}, {0, 0.5f, 0, 0}, {0, 0, 0.33333333333333f, 0}, {0, 0, 0, 0.25f}));
  }
}