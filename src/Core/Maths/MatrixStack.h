#include <stack>

#include "Maths/Maths.h"
#include "Maths/Rotate.h"

namespace Krys
{

  class MatrixStack
  {
  private:
    Mat4 m_CurrentMatrix;
    std::stack<Mat4> m_Matrices;

  public:
    MatrixStack() : m_CurrentMatrix(1.0f) {}

    const Mat4 &Top() const noexcept
    {
      return m_CurrentMatrix;
    }

    void RotateX(float degrees)
    {
      m_CurrentMatrix = m_CurrentMatrix * Mat4(Krys::RotateX(degrees));
    }

    void RotateY(float degrees)
    {
      m_CurrentMatrix = m_CurrentMatrix * Mat4(Krys::RotateY(degrees));
    }

    void RotateZ(float degrees)
    {
      m_CurrentMatrix = m_CurrentMatrix * Mat4(Krys::RotateZ(degrees));
    }

    void Scale(const Vec3 &scaleVec)
    {
      Mat4 scaleMat(1.0f);
      scaleMat[0].x = scaleVec.x;
      scaleMat[1].y = scaleVec.y;
      scaleMat[2].z = scaleVec.z;

      m_CurrentMatrix = m_CurrentMatrix * scaleMat;
    }

    void Translate(const Vec3 &offsetVec)
    {
      Mat4 translateMat(1.0f);
      translateMat[3] = Vec4(offsetVec, 1.0f);

      m_CurrentMatrix = m_CurrentMatrix * translateMat;
    }

    void Push()
    {
      m_Matrices.push(m_CurrentMatrix);
    }

    void Pop() noexcept
    {
      m_CurrentMatrix = m_Matrices.top();
      m_Matrices.pop();
    }
  };
}