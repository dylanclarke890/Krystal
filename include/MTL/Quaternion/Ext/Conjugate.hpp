#pragma once

#include "MTL/Quaternion/Quat.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent>
  constexpr Quaternion<TComponent> Conjugate(const Quaternion<TComponent> &quat) noexcept
  {
    return Quaternion<TComponent>(quat.w, -quat.x, -quat.y, -quat.z);
  }
}