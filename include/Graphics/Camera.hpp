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

    /// @brief Translate the camera.
    /// @param translation the translation vector.
    void Translate(const Vec3 &translation) noexcept;

    /// @brief Get the projection matrix of the camera.
    NO_DISCARD const Mat4 &GetProjection() const noexcept;

    /// @brief Get the view matrix of the camera.
    NO_DISCARD const Mat4 &GetView() const noexcept;

    /// @brief Set the view matrix of the camera.
    /// @param view the new view matrix.
    void SetView(const Mat4 &view) noexcept;

    /// @brief Get position of camera
    NO_DISCARD const Vec3 &GetPosition() const noexcept;

    /// @brief Set the position of the camera.
    /// @param position the new position.
    void SetPosition(const Vec3 &position) noexcept;

    /// @brief Calculates the orientation of the camera.
    NO_DISCARD MTL::Quat GetOrientation() const noexcept;

    /// @brief Get the direction the camera is facing.
    NO_DISCARD const Vec3 &GetDirection() const noexcept;

    /// @brief Set the direction the camera is facing.
    /// @param direction the new direction.
    void SetDirection(const Vec3 &direction) noexcept;

    /// @brief Calculates the right vector of the camera.
    NO_DISCARD Vec3 GetRight() const noexcept;

    /// @brief Gets the up vector of the camera.
    NO_DISCARD Vec3 GetUp() const noexcept;

    /// @brief Get the yaw of the camera.
    NO_DISCARD float GetYaw() const noexcept;

    /// @brief Set the yaw of the camera.
    /// @param yaw the new yaw.
    void SetYaw(float yaw) noexcept;

    /// @brief Adjust the yaw of the camera.
    /// @param by the amount to adjust the yaw by.
    void AdjustYaw(float by) noexcept;

    /// @brief Get the pitch of the camera.
    NO_DISCARD float GetPitch() const noexcept;

    /// @brief Set the pitch of the camera.
    /// @param pitch the new pitch.
    void SetPitch(float pitch) noexcept;

    /// @brief Adjust the pitch of the camera.
    /// @param by the amount to adjust the pitch by.
    void AdjustPitch(float by) noexcept;

    /// @brief Get the type of the camera.
    NO_DISCARD CameraType GetType() const noexcept;

    /// @brief Look at a target.
    /// @param target the target to look at.
    void LookAt(const Vec3 &target) noexcept;

  private:
    /// @brief Camera position in world space.
    Vec3 _position;

    /// @brief Direction the camera is facing.
    Vec3 _direction;

    /// @brief Up vector of the camera.
    Vec3 _up;

    /// @brief View matrix of the camera.
    Mat4 _view;

    /// @brief Projection matrix of the camera.
    Mat4 _projection;

    /// @brief Pitch of camera.
    float _pitch;

    /// @brief Yaw of camera.
    float _yaw;

    /// @brief Type of the camera.
    CameraType _type;
  };
}