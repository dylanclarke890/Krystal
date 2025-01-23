#include "Graphics/Camera.hpp"

#include "MTL/Common/Constants.hpp"
#include "MTL/Matrices/Ext/ClipSpace.hpp"
#include "MTL/Matrices/Ext/Transformations.hpp"
#include "MTL/Trigonometric/Cos.hpp"
#include "MTL/Trigonometric/Sin.hpp"

namespace Krys::Gfx
{
  static Vec3 CreateDirection(float pitch, float yaw)
  {
    Vec3 direction;

    direction.x = MTL::Cos(yaw) * MTL::Cos(pitch);
    direction.y = MTL::Sin(pitch);
    direction.z = MTL::Sin(yaw) * MTL::Cos(pitch);

    return MTL::Normalize(direction);
  }

  Camera::Camera(CameraType type, uint32 width, uint32 height, uint32 depth)
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

  Mat4 Camera::GetProjection() const
  {
    return _projection;
  }

  Mat4 Camera::GetView() const
  {
    return _view;
  }

  void Camera::SetView(const Mat4 &view) noexcept
  {
    _view = view;
  }

  Vec3 Camera::GetPosition() const noexcept
  {
    return _position;
  }

  void Camera::SetPosition(const Vec3 &position) noexcept
  {
    _position = position;
    _view = MTL::LookAt(_position, _position + _direction, _up);
  }

  MTL::Quat Camera::GetOrientation() const
  {
    return {_yaw, _pitch, 0.0f};
  }

  Vec3 Camera::GetDirection() const
  {
    return _direction;
  }

  Vec3 Camera::GetRight() const
  {
    return MTL::Normalize(MTL::Cross(_direction, _up));
  }

  float Camera::GetYaw() const
  {
    return _yaw;
  }

  void Camera::SetYaw(float yaw)
  {
    _yaw = yaw;
    _direction = CreateDirection(_pitch, _yaw);
    _view = MTL::LookAt(_position, _position + _direction, _up);
  }

  void Camera::AdjustYaw(float by)
  {
    SetYaw(_yaw + by);
  }

  float Camera::GetPitch() const
  {
    return _pitch;
  }

  void Camera::SetPitch(float pitch)
  {
    _pitch = pitch;
    _direction = CreateDirection(_pitch, _yaw);
    _view = MTL::LookAt(_position, _position + _direction, _up);
  }

  void Camera::AdjustPitch(float by)
  {
    SetPitch(_pitch + by);
  }

  CameraType Camera::GetType() const
  {
    return _type;
  }
}