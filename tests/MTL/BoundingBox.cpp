#include "MTL/BoundingBox.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_BoundingBox()
  {
    // Default Constructor
    constexpr BoundingBox<float> defaultBox;
    KRYS_EXPECT_EQUAL("Default Constructor - Left", defaultBox.Left, 0.0f);
    KRYS_EXPECT_EQUAL("Default Constructor - Right", defaultBox.Right, 0.0f);
    KRYS_EXPECT_EQUAL("Default Constructor - Bottom", defaultBox.Bottom, 0.0f);
    KRYS_EXPECT_EQUAL("Default Constructor - Top", defaultBox.Top, 0.0f);
    KRYS_EXPECT_EQUAL("Default Constructor - Width", defaultBox.GetWidth(), 0.0f);
    KRYS_EXPECT_EQUAL("Default Constructor - Height", defaultBox.GetHeight(), 0.0f);

    // Parameterized Constructor
    constexpr BoundingBox<float> paramBox(-1.0f, 1.0f, -2.0f, 2.0f);
    KRYS_EXPECT_EQUAL("Parameterized Constructor - Left", paramBox.Left, -1.0f);
    KRYS_EXPECT_EQUAL("Parameterized Constructor - Right", paramBox.Right, 1.0f);
    KRYS_EXPECT_EQUAL("Parameterized Constructor - Bottom", paramBox.Bottom, -2.0f);
    KRYS_EXPECT_EQUAL("Parameterized Constructor - Top", paramBox.Top, 2.0f);
    KRYS_EXPECT_EQUAL("Parameterized Constructor - Width", paramBox.GetWidth(), 2.0f);
    KRYS_EXPECT_EQUAL("Parameterized Constructor - Height", paramBox.GetHeight(), 4.0f);

    // Zero Width/Height Box
    constexpr BoundingBox<float> zeroBox(1.0f, 1.0f, 2.0f, 2.0f);
    KRYS_EXPECT_EQUAL("Zero Box - Width", zeroBox.GetWidth(), 0.0f);
    KRYS_EXPECT_EQUAL("Zero Box - Height", zeroBox.GetHeight(), 0.0f);

    // Negative Dimensions
    constexpr BoundingBox<float> negBox(2.0f, -2.0f, 3.0f, -3.0f);
    KRYS_EXPECT_EQUAL("Negative Box - Left", negBox.Left, 2.0f);
    KRYS_EXPECT_EQUAL("Negative Box - Right", negBox.Right, -2.0f);
    KRYS_EXPECT_EQUAL("Negative Box - Bottom", negBox.Bottom, 3.0f);
    KRYS_EXPECT_EQUAL("Negative Box - Top", negBox.Top, -3.0f);
    KRYS_EXPECT_EQUAL("Negative Box - Width", negBox.GetWidth(), -4.0f);
    KRYS_EXPECT_EQUAL("Negative Box - Height", negBox.GetHeight(), -6.0f);
  }
}
