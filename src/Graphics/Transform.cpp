#include "Graphics/Transform.hpp"
#include "MTL/Matrices/Ext/Transformations.hpp"
#include "MTL/Vectors/Ext/Geometric.hpp"

#include <tuple>

namespace Krys::Impl
{
  /// @brief Decomposes a transformation matrix into translation, rotation and scale components.
  /// @param matrix The matrix to decompose.
  /// @return A tuple containing the translation, rotation and scale components.
  std::tuple<Vec3, Quat, Vec3> Decompose(const Mat4 &matrix) noexcept
  {
    const auto &[x, y, z, w] = matrix[3];
    const Vec3 translation {x, y, z};
    const Vec3 scale = {MTL::Length(matrix[0u]), MTL::Length(matrix[1u]), MTL::Length(matrix[2u])};

    // convert upper left 3x3 matrix to rotation matrix
    const auto &[c00, c01, c02, c03] = matrix[0];
    const auto &[c10, c11, c12, c13] = matrix[1];
    const auto &[c20, c21, c22, c23] = matrix[2];

    Mat4 rotationMatrix = Mat4 {{c00 / scale.x, c01 / scale.y, c02 / scale.z, 0.0f},
                                {c10 / scale.x, c11 / scale.y, c12 / scale.z, 0.0f},
                                {c20 / scale.x, c21 / scale.y, c22 / scale.z, 0.0f},
                                {0.0f, 0.0f, 0.0f, 1.0f}};

    // extract rotation
    Quat rotation {rotationMatrix};

    return {translation, rotation, scale};
  }
}

namespace Krys::Gfx
{
  Transform::Transform() noexcept : Transform(Vec3 {}, Quat {}, {1.0f})
  {
  }

  Transform::Transform(const Mat4 &matrix) noexcept : Transform(Vec3 {0.0f}, Quat {}, {0.0f})
  {
    const auto [translation, rotation, scale] = Impl::Decompose(matrix);

    _translation = translation;
    _rotation = rotation;
    _scale = scale;
  }

  Transform::Transform(const Vec3 &translation, const Quat &rotation, const Vec3 &scale) noexcept
      : _translation(translation), _rotation(rotation), _scale(scale)
  {
  }

  Mat4 Transform::GetMatrix() const noexcept
  {
    return MTL::Translate(Mat4(1.0f), _translation) * _rotation.ToMat4x4() * MTL::Scale(Mat4(1.0f), _scale);
  }

  void Transform::SetMatrix(const Mat4 &matrix) noexcept
  {
    const auto [translation, rotation, scale] = Impl::Decompose(matrix);

    _translation = translation;
    _rotation = rotation;
    _scale = scale;
  }

  // TODO:
  // void Transform::Interpolate(const Transform &other, float amount) noexcept
  // {
  //   _translation.lerp(other._translation, amount);
  //   _rotation.slerp(other._rotation, amount);
  //   _scale.lerp(other._scale, amount);
  // }

  Vec3 Transform::GetTranslation() const noexcept
  {
    return _translation;
  }

  void Transform::SetTranslation(const Vec3 &translation) noexcept
  {
    _translation = translation;
  }

  Quat Transform::GetRotation() const noexcept
  {
    return _rotation;
  }

  void Transform::SetRotation(const Quat &rotation) noexcept
  {
    _rotation = rotation;
  }

  Vec3 Transform::GetScale() const noexcept
  {
    return _scale;
  }

  void Transform::SetScale(const Vec3 &scale) noexcept
  {
    _scale = scale;
  }

  bool Transform::operator==(const Transform &other) const noexcept
  {
    return (_translation == other._translation) && (_rotation == other._rotation) && (_scale == other._scale);
  }

  bool Transform::operator!=(const Transform &other) const noexcept
  {
    return !(*this == other);
  }

  Transform Transform::operator*(const Transform &other) const noexcept
  {
    return Transform {*this} *= other;
  }

  Transform &Transform::operator*=(const Transform &other) noexcept
  {
    return *this *= other.GetMatrix();
  }

  Transform Transform::operator*(const Mat4 &other) const noexcept
  {
    return Transform {*this} *= other;
  }

  Transform &Transform::operator*=(const Mat4 &other) noexcept
  {
    auto result = GetMatrix() * other;
    const auto [translation, rotation, scale] = Impl::Decompose(result);

    _translation = translation;
    _rotation = rotation;
    _scale = scale;

    return *this;
  }

}