#include "Maths/Vector.h"

namespace Krys::Maths
{
  constexpr float PI32 = 3.1415927f;
  constexpr double PI64 = 3.141592653589793;

  inline constexpr float DegToRad(float degrees) noexcept
  {
    constexpr float ratio = PI32 * 2.0f / 360.0f;
    return degrees * ratio;
  }

  Mat3 RotateX(float degrees)
  {
    float radians = DegToRad(degrees);
    float cosRadians = cosf(radians);
    float sinRadians = sinf(radians);

    Mat3 matrix(1.0f);
    matrix[1].y = cosRadians;
    matrix[2].y = -sinRadians;
    matrix[1].z = sinRadians;
    matrix[2].z = cosRadians;
    return matrix;
  }

  Mat3 RotateY(float degrees)
  {
    float radians = DegToRad(degrees);
    float cosRadians = cosf(radians);
    float sinRadians = sinf(radians);

    Mat3 matrix(1.0f);
    matrix[0].x = cosRadians;
    matrix[2].x = sinRadians;
    matrix[0].z = -sinRadians;
    matrix[2].z = cosRadians;
    return matrix;
  }

  Mat3 RotateZ(float degrees)
  {
    float radians = DegToRad(degrees);
    float cosRadians = cosf(radians);
    float sinRadians = sinf(radians);

    Mat3 matrix(1.0f);
    matrix[0].x = cosRadians;
    matrix[1].x = -sinRadians;
    matrix[0].y = sinRadians;
    matrix[1].y = cosRadians;
    return matrix;
  }
}