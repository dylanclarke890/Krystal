#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Quaternion/Quat.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Gfx
{
  enum class CameraType : uint8
  {
    Perspective,
    Orthographic
  };

  /// @brief Represents a camera through which a scene is viewed/rendered.
  class Camera
  {
  public:
    /// @brief Create a new camera, positioned at the origin.
    /// @param type the type of the camera.
    /// @param width the width of the window.
    /// @param height the height of the window.
    /// @param depth the depth of the projection.
    Camera(CameraType type, uint32 width, uint32 height, uint32 depth = 1'000u) noexcept;

    /// @brief Get the position of the camera.
    NO_DISCARD const Vec3 &GetPosition() const noexcept;

    /// @brief Set the position of the camera.
    /// @param position the new position.
    void SetPosition(const Vec3 &position) noexcept;

    /// @brief Get the orientation of the camera.
    NO_DISCARD const Quat &GetOrientation() const noexcept;

    /// @brief Set the orientation of the camera.
    /// @param orientation the new orientation.
    void SetOrientation(const Quat &orientation) noexcept;

    /// @brief Get the view matrix of the camera.
    NO_DISCARD const Mat4 &GetView() const noexcept;

    /// @brief Get the projection matrix of the camera.
    NO_DISCARD const Mat4 &GetProjection() const noexcept;

    /// @brief Get the type of the camera.
    NO_DISCARD CameraType GetType() const noexcept;

    /// @brief Get the forward (direction) vector of the camera.
    NO_DISCARD Vec3 GetForward() const noexcept;

    /// @brief Set the direction of the camera.
    /// @param direction the new direction.
    void SetDirection(const Vec3 &direction) noexcept;

    /// @brief Get the right vector of the camera.
    NO_DISCARD Vec3 GetRight() const noexcept;

    /// @brief Get the up vector of the camera.
    NO_DISCARD Vec3 GetUp() const noexcept;

    /// @brief Translate the camera.
    /// @param translation the translation vector.
    void Translate(const Vec3 &translation) noexcept;

    /// @brief Rotate the camera using a quaternion.
    /// @param rotation the quaternion rotation to apply.
    void Rotate(const Quat &rotation) noexcept;

    /// @brief Look at a target point.
    /// @param target the target to look at.
    void LookAt(const Vec3 &target) noexcept;

  protected:
    /// @brief Width of the camera viewport.
    float _width;

    /// @brief Height of the camera viewport.
    float _height;

    /// @brief Camera position in world space.
    Vec3 _position;

    /// @brief Camera orientation as a quaternion.
    Quat _orientation;

    /// @brief View matrix of the camera.
    Mat4 _view;

    /// @brief Projection matrix of the camera.
    Mat4 _projection;

    /// @brief Type of the camera.
    CameraType _type;

    /// @brief Update the view matrix based on position and orientation.
    void UpdateViewMatrix() noexcept;
  };
}
