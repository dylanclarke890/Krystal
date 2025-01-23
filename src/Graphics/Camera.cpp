#include "Graphics/Camera.hpp"

#include "MTL/Common/Constants.hpp"
#include "MTL/Matrices/Ext/ClipSpace.hpp"
#include "MTL/Matrices/Ext/Transformations.hpp"
#include "MTL/Trigonometric/Cos.hpp"
#include "MTL/Trigonometric/Sin.hpp"

namespace Krys::Gfx
{
  static Vec3 CreateDirection(float pitch, float yaw) noexcept
  {
    Vec3 direction;

    direction.x = MTL::Cos(yaw) * MTL::Cos(pitch);
    direction.y = MTL::Sin(pitch);
    direction.z = MTL::Sin(yaw) * MTL::Cos(pitch);

    return MTL::Normalize(direction);
  }

  Camera::Camera(CameraType type, uint32 width, uint32 height, uint32 depth) noexcept
      : _position(0.0f, 0.0f, 100.0f), _direction(0.0f, 0.0f, -1.0f), _up(0.0f, 1.0f, 0.0f), _view(),
        _projection(), _pitch(0.0f), _yaw(-MTL::HalfPi<float>()), _type(type)
  {
    const auto widthF = static_cast<float>(width);
    const auto heightF = static_cast<float>(height);
    const auto depthF = static_cast<float>(depth);
    const auto fovy = 0.785398f;

    switch (_type)
    {
      case CameraType::Orthographic: _projection = MTL::Ortho(widthF, heightF, depthF); break;
      case CameraType::Perspective:
        _projection = MTL::Perspective(fovy, widthF, heightF, 0.1f, depthF);
        break;
      default: KRYS_ASSERT(false, "Unknown enum value: camera type"); break;
    }

    _direction = CreateDirection(_pitch, _yaw);
    _view = MTL::LookAt(_position, _position + _direction, _up);

    Logger::Info("Camera created.");
  }

  void Camera::Translate(const Vec3 &translation) noexcept
  {
    _position += translation;
    _view = MTL::LookAt(_position, _position + _direction, _up);
  }

  const Mat4 &Camera::GetProjection() const noexcept
  {
    return _projection;
  }

  const Mat4 &Camera::GetView() const noexcept
  {
    return _view;
  }

  void Camera::SetView(const Mat4 &view) noexcept
  {
    _view = view;
  }

  const Vec3 &Camera::GetPosition() const noexcept
  {
    return _position;
  }

  void Camera::SetPosition(const Vec3 &position) noexcept
  {
    _position = position;
    _view = MTL::LookAt(_position, _position + _direction, _up);
  }

  MTL::Quat Camera::GetOrientation() const noexcept
  {
    return {_yaw, _pitch, 0.0f};
  }

  const Vec3 &Camera::GetDirection() const noexcept
  {
    return _direction;
  }

  Vec3 Camera::GetRight() const noexcept
  {
    return MTL::Normalize(MTL::Cross(_direction, _up));
  }

  float Camera::GetYaw() const noexcept
  {
    return _yaw;
  }

  void Camera::SetYaw(float yaw) noexcept
  {
    _yaw = yaw;
    _direction = CreateDirection(_pitch, _yaw);
    _view = MTL::LookAt(_position, _position + _direction, _up);
  }

  void Camera::AdjustYaw(float by) noexcept
  {
    SetYaw(_yaw + by);
  }

  float Camera::GetPitch() const noexcept
  {
    return _pitch;
  }

  void Camera::SetPitch(float pitch) noexcept
  {
    _pitch = pitch;
    _direction = CreateDirection(_pitch, _yaw);
    _view = MTL::LookAt(_position, _position + _direction, _up);
  }

  void Camera::AdjustPitch(float by) noexcept
  {
    SetPitch(_pitch + by);
  }

  CameraType Camera::GetType() const noexcept
  {
    return _type;
  }
}