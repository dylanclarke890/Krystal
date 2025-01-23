#pragma once

#include "MTL/Quaternion/Ext/Conjugate.hpp"
#include "MTL/Quaternion/Quat.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent>
  Vec3 Rotate(const Quaternion<TComponent> &quat, const Vec3 &vec)
  {
    // Convert the vector to a quaternion with w = 0
    Quaternion<TComponent> vecQuat(0.0f, vec.x, vec.y, vec.z);

    // Perform the rotation: q * v * q^-1
    Quaternion<TComponent> quatConjugate = Conjugate(quat); // q^-1
    Quaternion<TComponent> rotatedQuat = quat * vecQuat * quatConjugate;

    // Extract the rotated vector (x, y, z) from the resulting quaternion
    return Vec3(rotatedQuat.x, rotatedQuat.y, rotatedQuat.z);
  }
}