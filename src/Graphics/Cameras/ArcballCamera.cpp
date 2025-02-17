#include "Graphics/Cameras/ArcballCamera.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Matrices/Ext/Transformations.hpp"
#include "MTL/Quaternion/Ext/Transform.hpp"
#include "MTL/Vectors/Ext/Abs.hpp"
#include "MTL/Vectors/Ext/Format.hpp"

namespace Krys::Gfx
{
  ArcballCamera::ArcballCamera(CameraType type, uint32 width, uint32 height, uint32 depth, const Vec3 &target,
                               float distance) noexcept
      : Camera(type, width, height, depth), _distance(distance), _target(target), _lastSpherePosition(0.0f)
  {
    UpdateOrbit();
  }

  void ArcballCamera::OnMouseDragStart(const Vec2 &position) noexcept
  {
    _lastSpherePosition = MapToSphere(position);
  }

  void ArcballCamera::OnMouseDrag(const Vec2 &position) noexcept
  {
    // Map current mouse to sphere
    Vec3 currentSpherePos = MapToSphere(position);

    // Compute rotation only if there's a meaningful difference
    if (currentSpherePos != _lastSpherePosition)
    {
      // Axis = p1 x p2
      Vec3 axis = MTL::Cross(_lastSpherePosition, currentSpherePos);
      float axisLen = MTL::Length(axis);
      if (axisLen > 1e-5f)
      {
        axis = axis / axisLen; // normalize

        // Dot product for the angle
        float dot = MTL::Dot(_lastSpherePosition, currentSpherePos);
        _lastSpherePosition = currentSpherePos;

        // clamp to avoid numerical issues
        float angle = MTL::Acos(MTL::Clamp(dot, -1.0f, 1.0f));

        // Apply this rotation to our orientation
        _orientation = _orientation * Quat(axis, angle * 1.5f);
        _orientation.Normalize();

        // Recompute the camera orbit
        UpdateOrbit();
      }
    }
  }

  void ArcballCamera::Zoom(float delta) noexcept
  {
    _distance += -delta;
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
    // 1. Compute camera position from orientation and distance
    //    By default, camera looks down -Z in local space, so place at (0,0,-_distance)
    Vec3 offset(0.f, 0.f, -_distance);

    // Rotate offset by our current orientation
    Vec3 finalPos = MTL::Rotate(_orientation, offset);

    // The actual camera world position is target + the offset
    _position = _target + finalPos;

    UpdateViewMatrix();
  }

  Vec3 ArcballCamera::MapToSphere(const Vec2 &mousePos) noexcept
  {
    Vec2 position = mousePos;
    Vec2 delta = MTL::Abs(_lastMousePosition - position);
    if (delta.x < 5)
      position.x = _lastMousePosition.x;
    if (delta.y < 5)
      position.y = _lastMousePosition.y;
    _lastMousePosition = position;

    // Convert [0..windowWidth], [0..windowHeight] to [-1..+1], [-1..+1]
    // Usually the center of the window is (0,0) in trackball space,
    // or you can define top-left as (-1,+1).
    // This is flexible; pick a scheme that works for your UI.

    // Example: center-based
    float x = (position.x - 0.5f * _width) / (0.5f * _width);
    float y = (0.5f * _height - position.y) / (0.5f * _height);
    // we invert y so that up is +y

    // Compute z = sqrt(1 - x^2 - y^2), clamp to 0 if outside
    float lengthSq = x * x + y * y;
    float z = 0.f;
    if (lengthSq < 1.0f)
      z = MTL::Sqrt(1.0f - lengthSq);
    else
    {
      // If the mouse is outside the sphere, project onto the sphere
      float length = MTL::Sqrt(lengthSq);
      x /= length;
      y /= length;
      // z stays 0
    }
    // TODO: this is a bit of a hack, but it works
    x = -x;

    auto result = Vec3(x, y, z);
    return result;
  }
}