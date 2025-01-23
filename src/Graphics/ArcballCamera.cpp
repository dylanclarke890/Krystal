#include "Graphics/ArcballCamera.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Matrices/Ext/Transformations.hpp"

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

    float xAngle = dx * deltaAngleX;
    float yAngle = dy * deltaAngleY;

    // Step 2: Handle edge case where direction aligns with up vector
    Vec3 direction = MTL::Normalize(_camera.GetPosition() - _target);
    Vec3 up = _camera.GetUp();
    // float cosAngle = MTL::Dot(direction, up);
    // if (MTL::Abs(cosAngle) > 0.99f)
    // {
    //   yAngle = 0; // Prevent rotation when direction is nearly parallel to up vector
    // }

    // Step 3: Rotate the camera position around the target
    Vec3 position = _camera.GetPosition();

    // Rotate around the up vector (yaw)
    Mat4 rotationX = MTL::Rotate(Mat4(1.0f), xAngle, up);
    position = Vec3(rotationX * Vec4(position - _target, 1.0f)) + _target;

    // Rotate around the right vector (pitch)
    Vec3 right = MTL::Normalize(MTL::Cross(direction, up));
    Mat4 rotationY = MTL::Rotate(Mat4(1.0f), yAngle, right);
    position = Vec3(rotationY * Vec4(position - _target, 1.0f)) + _target;

    // Step 4: Update the camera
    _camera.SetPosition(position);
    _camera.LookAt(_target); // Always look at the fixed target
  }
  Camera &ArcballCamera::GetCamera() noexcept
  {
    return _camera;
  }
}