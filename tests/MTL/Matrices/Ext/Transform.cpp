#include "MTL/Matrices/Ext/Transform.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::MTL
{
  static void Test_Translate()
  {
    constexpr Mat4x4 mat {1};
    constexpr Vec3 translate {1, 3, 4};

    constexpr auto result = Translate(mat, translate);
  }
}