#include "MTL/Quaternion/Ext/Transform.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_RotateVec()
  {
    constexpr Quat quat = Quat(Vec3(0.0f, 1.0f, 0.0f), MTL::HalfPi<float>());
    constexpr Vec3 forward(1.0f, 0.0f, 0.0f);
    constexpr Vec3 rotated = Rotate(quat, forward);
    KRYS_EXPECT_NEAR("Rotate", -rotated.z, 1.0f, 1e-6f);
  }

}