#include "Graphics/ArcballCamera.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Matrices/Ext/Transformations.hpp"
#include "MTL/Quaternion/Ext/Transformations.hpp"

namespace Krys::Gfx
{
  ArcballCamera::ArcballCamera(const Vec3 &position, const Vec3 &target, const Vec2ui &viewport) noexcept
      : _camera(CameraType::Perspective, viewport.x, viewport.y, 100), _viewport(viewport), _target(target)
  {
    _camera.SetPosition(position);
    _camera.LookAt(target);
  }

  void ArcballCamera::Update(float dx, float dy) noexcept
  {
    // Step 1: Calculate rotation angles based on mouse movement
    float deltaAngleX = MTL::TwoPi<float>() / _viewport.x; // Full rotation for viewport width
    float deltaAngleY = MTL::Pi<float>() / _viewport.y;    // Half rotation for viewport height

    float yawAngle = dx * deltaAngleX;   // Horizontal rotation
    float pitchAngle = dy * deltaAngleY; // Vertical rotation

    // Step 2: Create quaternions for the yaw and pitch rotations
    Vec3 up = Vec3(0.0f, 1.0f, 0.0f); // Fixed world up for yaw
    Vec3 direction = MTL::Normalize(_camera.GetPosition() - _target);
    Vec3 right = MTL::Normalize(MTL::Cross(up, direction)); // Right vector for pitch

    // Quaternion for yaw (around world up)
    MTL::Quat yawRotation = MTL::Quat(up, yawAngle);

    // Quaternion for pitch (around local right vector)
    MTL::Quat pitchRotation = MTL::Quat(right, pitchAngle);

    // Step 3: Combine the rotations
    MTL::Quat totalRotation = pitchRotation * yawRotation;

    // Step 4: Rotate the camera position using the combined quaternion
    Vec3 position = _camera.GetPosition() - _target; // Relative to target
    position = MTL::Rotate(totalRotation, position) + _target;

    // Step 5: Update the camera
    _camera.SetPosition(position);
    _camera.SetDirection(MTL::Normalize(_target - position)); // Look at the target
  }

  Camera &ArcballCamera::GetCamera() noexcept
  {
    return _camera;
  }
}