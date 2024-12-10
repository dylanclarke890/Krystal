#include "MTL/Vectors/Ext/Ranges.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  template <vec_length_t L>
  constexpr float TestHelper_SumVector(const vector_t<float, L> &vec)
  {
    float total = 0;
    for (auto it = Begin(vec); it != End(vec); ++it)
      total += *it;
    return total;
  }

  static void Test_Vec1_Ranges()
  {
    using vec_t = vector_t<float, 1>;
    constexpr vec_t vec(1);

    constexpr float sum = TestHelper_SumVector(vec);
    KRYS_EXPECT_EQUAL("Ranges Vec1", sum, 1);
  }

  static void Test_Vec2_Ranges()
  {
    using vec_t = vector_t<float, 2>;
    constexpr vec_t vec(1, 2);

    constexpr float sum = TestHelper_SumVector(vec);
    KRYS_EXPECT_EQUAL("Ranges Vec2", sum, 3);
  }

  static void Test_Vec3_Ranges()
  {
    using vec_t = vector_t<float, 3>;
    constexpr vec_t vec(1, 2, 3);

    constexpr float sum = TestHelper_SumVector(vec);
    KRYS_EXPECT_EQUAL("Ranges Vec3", sum, 6);
  }

  static void Test_Vec4_Ranges()
  {
    using vec_t = vector_t<float, 4>;
    constexpr vec_t vec(1, 2, 3, 4);

    constexpr float sum = TestHelper_SumVector(vec);
    KRYS_EXPECT_EQUAL("Ranges Vec4", sum, 10);
  }
}
