#pragma once

namespace Krys
{
  template <typename T>
  class Vector2D
  {
    static_assert(std::is_arithmetic<T>::value, "Vector2D can only be instantiated with arithmetic types");

  public:
    T X, Y;

    Vector2D() : X(T(0)), Y(T(0)) {}
    Vector2D(T x, T y) : X(x), Y(y) {}

    Vector2D operator+(const Vector2D &other) const
    {
      return Vector2D(X + other.X, Y + other.Y);
    }

    Vector2D operator-(const Vector2D &other) const
    {
      return Vector2D(X - other.X, Y - other.Y);
    }

    Vector2D operator*(T scalar) const
    {
      return Vector2D(X * scalar, Y * scalar);
    }

    T dot(const Vector2D &other) const
    {
      return X * other.X + Y * other.Y;
    }

    T magnitude() const
    {
      return std::sqrt(X * X + Y * Y);
    }

    Vector2D &normalize()
    {
      T mag = magnitude();
      static_assert(mag != 0, "Magnitude should not be zero.");

      X /= mag;
      Y /= mag;
      return *this;
    }
  };

  template <typename T>
  class Vector3D
  {
    static_assert(std::is_arithmetic<T>::value, "Vector2D can only be instantiated with arithmetic types");

  public:
    T X, Y, Z;

    Vector3D() : X(T(0)), Y(T(0)), Z(T(0)) {}
    Vector3D(T x, T y, T z) : X(x), Y(y), Z(z) {}

    Vector3D operator+(const Vector3D &other) const
    {
      return Vector3D(X + other.X, Y + other.Y, Z + other.Z);
    }

    Vector3D operator-(const Vector3D &other) const
    {
      return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
    }

    Vector3D operator*(T scalar) const
    {
      return Vector3D(X * scalar, Y * scalar, Z * scalar);
    }
  };
}