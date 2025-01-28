#pragma once

#include "Base/Types.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Quaternion/Quat.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Gfx
{
  /// @brief Represents a transformation in 3D space.
  /// @note A transformation is formed of a translation, rotation and scale.
  class Transform
  {
  public:
    /// @brief Constructs a transform which represents zero translation, zero rotation and scale of 1.
    Transform() noexcept;

    /// @brief Constructs a transform from a matrix.
    /// @param matrix The matrix to extract the translation, rotation and scale from.
    explicit Transform(const Mat4 &matrix) noexcept;

    /// @brief Constructs a transform from component parts.
    /// @param translation The translation component.
    /// @param rotation The rotation component.
    /// @param scale The scale component.
    Transform(const Vec3 &translation, const Quat &rotation, const Vec3 &scale) noexcept;

    Mat4 GetMatrix() const noexcept;

    /// @brief Sets the transform from a matrix.
    /// @param matrix The matrix to extract the translation, rotation and scale from.
    void SetMatrix(const Mat4 &matrix) noexcept;

    /// @brief Interpolates between this and another Transform.
    /// @param other The transform to interpolate to.
    /// @param amount The interpolation amount, must be in the range [0, 1].
    // TODO:
    // void Interpolate(const Transform &other, float amount) noexcept;

    /// @brief Get the translation component of the transform.
    Vec3 GetTranslation() const noexcept;

    /// @brief Set the translation component of the transform.
    /// @param translation The new translation.
    void SetTranslation(const Vec3 &translation) noexcept;

    /// @brief Get the rotation component of the transform.
    Quat GetRotation() const noexcept;

    /// @brief Set the rotation component of the transform.
    /// @param rotation The new rotation.
    void SetRotation(const Quat &rotation) noexcept;

    /// @brief Get the scale component of the transform.
    Vec3 GetScale() const noexcept;

    /// @brief Set the scale component of the transform.
    /// @param scale The new scale.
    void SetScale(const Vec3 &scale) noexcept;

    /// @brief Equality operator.
    /// @param other The transform to compare against.
    bool operator==(const Transform &other) const noexcept;

    /// @brief Inequality operator.
    /// @param other The transform to compare against.
    bool operator!=(const Transform &other) const noexcept;

    /// @brief Multiply operator.
    /// @param other The transform to multiply by.
    /// @returns The new transform, which is this transform followed by the supplied one.
    Transform operator*(const Transform &other) const noexcept;

    /// @brief Multiply operator.
    /// @param other The transform to multiply by.
    /// @returns This transform after the supplied transform has been applied.
    Transform &operator*=(const Transform &other) noexcept;

    /// @brief Multiply operator.
    /// @param other The matrix to multiply by.
    /// @returns The new transform, which is this transform followed by the supplied matrix.
    Transform operator*(const Mat4 &other) const noexcept;

    /// @brief Multiply operator.
    /// @param other The matrix to multiply by.
    /// @returns This transform after the supplied matrix has been applied.
    Transform &operator*=(const Mat4 &other) noexcept;

  private:
    /// @brief Translation component.
    Vec3 _translation;

    /// @brief Rotation component.
    Quat _rotation;

    /// @brief Scale component.
    Vec3 _scale;
  };
}