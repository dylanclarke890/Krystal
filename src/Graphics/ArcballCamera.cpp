#include "Graphics/ArcballCamera.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Matrices/Ext/Transformations.hpp"
#include "MTL/Quaternion/Ext/Transform.hpp"

namespace Krys::Gfx
{
  ArcballCamera::ArcballCamera(CameraType type, uint32 width, uint32 height, uint32 depth, const Vec3 &target,
                               float distance) noexcept
      : Camera(type, width, height, depth), _distance(distance), _target(target), _rotationX(0.0f),
        _rotationY(0.0f)
  {
    UpdateOrbit();
  }

  void ArcballCamera::OnMouseDrag(float deltaX, float deltaY) noexcept
  {
    // Sensitivity factors
    const float rotationSpeed = 0.01f;

    // Adjust angles
    _rotationY += deltaX * rotationSpeed; // yaw
    _rotationX += deltaY * rotationSpeed; // pitch

    // Clamp the pitch angle if you like (to avoid flipping)
    // e.g. _rotationX = std::clamp(_rotationX, -MTL::HalfPi<float>(), MTL::HalfPi<float>());

    UpdateOrbit();
  }

  void ArcballCamera::Zoom(float delta) noexcept
  {
    _distance += delta;
    if (_distance < 1.0f)
      _distance = 1.0f; // prevent going through target

    UpdateOrbit();
  }

  void ArcballCamera::SetTarget(const Vec3 &target) noexcept
  {
    _target = target;
    UpdateOrbit();
  }

  const Vec3 &ArcballCamera::GetTarget() const noexcept
  {
    return _target;
  }

  void ArcballCamera::UpdateOrbit() noexcept
  {
    // 1. Compute orientation from angles
    //    Let's define yaw = _rotationY, pitch = _rotationX
    Quat yawRotation = MTL::RotateY(_rotationY);
    Quat pitchRotation = MTL::RotateX(_rotationX);

    // The final orientation is pitch * yaw (apply yaw first, then pitch)
    Quat orbitRotation = pitchRotation * yawRotation;
    orbitRotation.Normalize();

    // 2. Compute camera position
    //    By default, the camera looks down -Z, so place it at (0, 0, _distance)
    Vec3 offset(0.f, 0.f, -_distance);

    // Rotate offset by orientation
    Vec3 finalPos = Krys::MTL::Rotate(orbitRotation, offset);

    // 3. The actual camera world position is target + the offset
    SetPosition(_target + finalPos);

    // 4. Set orientation
    SetOrientation(orbitRotation);
  }
}