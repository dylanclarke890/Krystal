#pragma once

#include "Graphics/Camera.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Gfx
{
  class ArcballCamera : public Camera
  {
  public:
    /// @brief Create a new arcball camera.
    /// @param type the type of the camera.
    /// @param width the width of the window.
    /// @param height the height of the window.
    /// @param depth the depth of the projection.
    ArcballCamera(CameraType type, uint32 width, uint32 height, uint32 depth, const Vec3 &target = Vec3(0.0f),
                  float distance = 100.f) noexcept;

    void OnMouseDragStart(const Vec2 &position) noexcept;
    void OnMouseDrag(const Vec2 &position) noexcept;

    /// @brief Zoom in/out (change orbit distance)
    void Zoom(float delta) noexcept;

    /// @brief Set the target point to look at.
    void SetTarget(const Vec3 &target) noexcept;

    /// @brief Get the target point being looked at.
    const Vec3 &GetTarget() const noexcept;

  protected:
    /// @brief Update the camera's orbit based on the current angles.
    void UpdateOrbit() noexcept;

  private:
    /// @brief Convert 2D mouse position to a 3D vector on the virtual sphere
    Vec3 MapToSphere(const Vec2 &mousePos) noexcept;

  private:
    /// @brief The fixed distance from the target.
    float _distance;

    // @brief The target point to look at.
    Vec3 _target;

    Vec2 _lastMousePosition{};

    /// @brief The last mouse position.
    Vec3 _lastSpherePosition;
  };
}