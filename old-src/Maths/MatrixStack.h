#include <stack>

#include "Maths/Rotate.h"
#include "Maths/Vector.h"

namespace Krys::Maths
{
  class MatrixStack
  {
  private:
    Mat4 _currentMatrix;
    std::stack<Mat4> _matrices;

  public:
    MatrixStack() : _currentMatrix(1.0f)
    {
    }

    const Mat4 &Top() const noexcept
    {
      return _currentMatrix;
    }

    void RotateX(float degrees)
    {
      _currentMatrix = _currentMatrix * Mat4(Krys::Maths::RotateX(degrees));
    }

    void RotateY(float degrees)
    {
      _currentMatrix = _currentMatrix * Mat4(Krys::Maths::RotateY(degrees));
    }

    void RotateZ(float degrees)
    {
      _currentMatrix = _currentMatrix * Mat4(Krys::Maths::RotateZ(degrees));
    }

    void Scale(const Vec3 &scaleVec)
    {
      Mat4 scaleMat(1.0f);
      scaleMat[0].x = scaleVec.x;
      scaleMat[1].y = scaleVec.y;
      scaleMat[2].z = scaleVec.z;

      _currentMatrix = _currentMatrix * scaleMat;
    }

    void Translate(const Vec3 &offsetVec)
    {
      Mat4 translateMat(1.0f);
      translateMat[3] = Vec4(offsetVec, 1.0f);

      _currentMatrix = _currentMatrix * translateMat;
    }

    void Push()
    {
      _matrices.push(_currentMatrix);
    }

    void Pop() noexcept
    {
      _currentMatrix = _matrices.top();
      _matrices.pop();
    }
  };
}