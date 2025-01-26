#include "Graphics/Cameras/Camera.hpp"

#include "MTL/Common/Constants.hpp"
#include "MTL/Common/Convert.hpp"
#include "MTL/Matrices/Ext/ClipSpace.hpp"
#include "MTL/Matrices/Ext/Transformations.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Quaternion/Ext/Transform.hpp"
#include "MTL/Trigonometric/Atan2.hpp"
#include "MTL/Trigonometric/Cos.hpp"
#include "MTL/Trigonometric/Sin.hpp"

namespace Krys::Gfx
{
  Camera::Camera(CameraType type, uint32 width, uint32 height, uint32 depth) noexcept
      : _width(static_cast<float>(width)), _height(static_cast<float>(height)), _position(0.0f, 0.0f, 100.0f),
        _orientation(), _view(), _projection(), _type(type)
  {
    const float depthF = static_cast<float>(depth);
    // TODO make this configurable
    constexpr float fovy = MTL::Radians(45.0f);

    switch (_type)
    {
      case CameraType::Orthographic: _projection = MTL::Ortho(_width, _height, depthF); break;
      case CameraType::Perspective:
        _projection = MTL::Perspective(fovy, _width / _height, 0.1f, depthF);
        break;
      default: KRYS_ASSERT(false, "Unknown enum value: camera type"); break;
    }

    UpdateViewMatrix();
    Logger::Info("Camera created.");
  }

  const Vec3 &Camera::GetPosition() const noexcept
  {
    return _position;
  }

  void Camera::SetPosition(const Vec3 &position) noexcept
  {
    _position = position;
    UpdateViewMatrix();
  }

  const Quat &Camera::GetOrientation() const noexcept
  {
    return _orientation;
  }

  void Camera::SetOrientation(const Quat &orientation) noexcept
  {
    _orientation = orientation;
    UpdateViewMatrix();
  }

  const Mat4 &Camera::GetProjection() const noexcept
  {
    return _projection;
  }

  const Mat4 &Camera::GetView() const noexcept
  {
    return _view;
  }

  CameraType Camera::GetType() const noexcept
  {
    return _type;
  }

  Vec3 Camera::GetForward() const noexcept
  {
    return MTL::Rotate(_orientation, Vec3(0.0f, 0.0f, -1.0f));
  }

  void Camera::SetDirection(const Vec3 &dir) noexcept
  {
    // Normalize the input direction
    Vec3 direction = MTL::Normalize(dir);

    // Define the default forward vector (camera's initial view direction)
    Vec3 forward = Vec3(0.0f, 0.0f, -1.0f);

    // Calculate the dot product between forward and the new direction
    float dot = MTL::Dot(forward, direction);

    // Handle edge cases
    if (dot > 0.9999f)
    {
      // New direction is the same as the forward vector
      _orientation = Quat(); // Identity quaternion
    }
    else if (dot < -0.9999f)
    {
      // New direction is directly opposite to the forward vector
      Vec3 up = Vec3(0.0f, 1.0f, 0.0f); // Choose an arbitrary orthogonal axis
      _orientation = Quat(up, MTL::Pi<float>());
    }
    else
    {
      // General case: Calculate rotation axis and angle
      Vec3 axis = MTL::Normalize(MTL::Cross(forward, direction));
      float angle = MTL::Acos(dot);

      // Create the quaternion representing the rotation
      _orientation = Quat(axis, angle);
    }

    // Update the view matrix
    UpdateViewMatrix();
  }

  Vec3 Camera::GetRight() const noexcept
  {
    return MTL::Rotate(_orientation, Vec3(1.0f, 0.0f, 0.0f));
  }

  Vec3 Camera::GetUp() const noexcept
  {
    return MTL::Rotate(_orientation, Vec3(0.0f, 1.0f, 0.0f));
  }

  void Camera::Translate(const Vec3 &translation) noexcept
  {
    _position += translation;
    UpdateViewMatrix();
  }

  void Camera::Rotate(const Quat &rotation) noexcept
  {
    // Compose the rotations using quaternion multiplication.
    _orientation = (rotation * _orientation).Normalize();
    UpdateViewMatrix();
  }

  void Camera::LookAt(const Vec3 &target) noexcept
  {
    // Compute the forward, right, and up vectors
    Vec3 forward = Normalize(target - _position);
    Vec3 right = MTL::Normalize(MTL::Cross(Vec3(0.0f, 1.0f, 0.0f), forward));
    Vec3 up = MTL::Cross(forward, right);

    // Compute the rotation matrix from the vectors
    Mat3 rotationMatrix(right, up, -forward);
    _orientation = Quat(rotationMatrix);

    UpdateViewMatrix();
  }

  void Camera::UpdateViewMatrix() noexcept
  {
    // Compute the rotation matrix from the quaternion
    Mat4 rotation = _orientation.Normalize().ToMat4x4();

    // Compute the translation matrix
    Mat4 translation = MTL::Translate(Mat4(1.0f), -_position);

    // View matrix is the inverse of the camera's world transformation.
    _view = rotation * translation;
  }
}