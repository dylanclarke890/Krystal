#pragma once

#include "MTL/Common/Clamp.hpp"
#include "MTL/Quaternion/Quat.hpp"

namespace Krys::MTL
{
  /// @brief Spherically interpolates between two quaternions.
  /// @param other the other quaternion.
  /// @param t the interpolation factor.
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr Quaternion<TComponent> Slerp(const Quaternion<TComponent> &a,
                                                    const Quaternion<TComponent> &b, TComponent t) noexcept
  {
    using quat_t = Quaternion<TComponent>;
    using component_t = TComponent;

    quat_t q1 = a;
    quat_t q2 = b;

    component_t dot = q1.Dot(q2);

    if (dot < 0.0f)
    {
      q2 = -q2;
      dot = -dot;
    }

    constexpr component_t threshold = 0.9995f;
    if (dot > threshold)
    {
      quat_t result = q1 + (q2 - q1) * t;
      result.Normalize();
      return result;
    }

    dot = Clamp(dot, -1.0f, 1.0f);
    component_t theta = Acos(dot);
    component_t sinTheta = Sin(theta);
    component_t sinTTheta = Sin(t * theta);

    component_t s0 = Cos(t * theta) - dot * sinTTheta / sinTheta;
    component_t s1 = sinTTheta / sinTheta;

    return q1 * s0 + q2 * s1;
  }
}
