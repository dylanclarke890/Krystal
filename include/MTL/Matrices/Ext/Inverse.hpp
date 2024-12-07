#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Determinant.hpp"

namespace Krys::MTL
{
  /// @brief Computes the inverse of `m`.
  /// @tparam TComponent The underlying floating point type of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @param m The input matrix.
  /// @return The inverse of `m`.
  template <IsFloatingPointT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto
    Inverse(const matrix_t<TComponent, RL, CL> &m) noexcept -> matrix_t<TComponent, RL, CL>
  {
    KRYS_STATIC_ASSERT_SQUARE_MATRIX(RL, CL);

    if constexpr (RL == 2 && CL == 2)
    {
      TComponent determinant = Determinant(m);
      if (determinant == TComponent(0))
        determinant = TComponent(1);

      TComponent oneOverDeterminant = TComponent(1) / determinant;
      return matrix_t<TComponent, 2, 2>(+m[1].y * oneOverDeterminant, -m[0].y * oneOverDeterminant,
                                        -m[1].x * oneOverDeterminant, +m[0].x * oneOverDeterminant);
    }
    else if constexpr (RL == 3 && CL == 3)
    {
      TComponent determinant = Determinant(m);
      if (determinant == TComponent(0))
        determinant = TComponent(1);
      TComponent oneOverDet = TComponent(1) / determinant;

      return matrix_t<TComponent, 3, 3>(+((m[1].y * m[2].z - m[2].y * m[1].z) * oneOverDet),
                                        -((m[0].y * m[2].z - m[2].y * m[0].z) * oneOverDet),
                                        +((m[0].y * m[1].z - m[1].y * m[0].z) * oneOverDet),

                                        -((m[1].x * m[2].z - m[2].x * m[1].z) * oneOverDet),
                                        +((m[0].x * m[2].z - m[2].x * m[0].z) * oneOverDet),
                                        -((m[0].x * m[1].z - m[1].x * m[0].z) * oneOverDet),

                                        +((m[1].x * m[2].y - m[2].x * m[1].y) * oneOverDet),
                                        -((m[0].x * m[2].y - m[2].x * m[0].y) * oneOverDet),
                                        +((m[0].x * m[1].y - m[1].x * m[0].y) * oneOverDet));
    }
    else if constexpr (RL == 4 && CL == 4)
    {
      TComponent A2323 = m[2].z * m[3].w - m[2].w * m[3].z;
      TComponent A1323 = m[2].y * m[3].w - m[2].w * m[3].y;
      TComponent A1223 = m[2].y * m[3].z - m[2].z * m[3].y;
      TComponent A0323 = m[2].x * m[3].w - m[2].w * m[3].x;
      TComponent A0223 = m[2].x * m[3].z - m[2].z * m[3].x;
      TComponent A0123 = m[2].x * m[3].y - m[2].y * m[3].x;
      TComponent A2313 = m[1].z * m[3].w - m[1].w * m[3].z;
      TComponent A1313 = m[1].y * m[3].w - m[1].w * m[3].y;
      TComponent A1213 = m[1].y * m[3].z - m[1].z * m[3].y;
      TComponent A2312 = m[1].z * m[2].w - m[1].w * m[2].z;
      TComponent A1312 = m[1].y * m[2].w - m[1].w * m[2].y;
      TComponent A1212 = m[1].y * m[2].z - m[1].z * m[2].y;
      TComponent A0313 = m[1].x * m[3].w - m[1].w * m[3].x;
      TComponent A0213 = m[1].x * m[3].z - m[1].z * m[3].x;
      TComponent A0312 = m[1].x * m[2].w - m[1].w * m[2].x;
      TComponent A0212 = m[1].x * m[2].z - m[1].z * m[2].x;
      TComponent A0113 = m[1].x * m[3].y - m[1].y * m[3].x;
      TComponent A0112 = m[1].x * m[2].y - m[1].y * m[2].x;

      TComponent det = m[0].x * (m[1].y * A2323 - m[1].z * A1323 + m[1].w * A1223)
                       - m[0].y * (m[1].x * A2323 - m[1].z * A0323 + m[1].w * A0223)
                       + m[0].z * (m[1].x * A1323 - m[1].y * A0323 + m[1].w * A0123)
                       - m[0].w * (m[1].x * A1223 - m[1].y * A0223 + m[1].z * A0123);

      if (det == TComponent(0))
        det = 1;
      det = TComponent(1) / det;

      return matrix_t<TComponent, 4, 4>({det * (m[1].y * A2323 - m[1].z * A1323 + m[1].w * A1223),
                                         det * -(m[0].y * A2323 - m[0].z * A1323 + m[0].w * A1223),
                                         det * (m[0].y * A2313 - m[0].z * A1313 + m[0].w * A1213),
                                         det * -(m[0].y * A2312 - m[0].z * A1312 + m[0].w * A1212)},
                                        {det * -(m[1].x * A2323 - m[1].z * A0323 + m[1].w * A0223),
                                         det * (m[0].x * A2323 - m[0].z * A0323 + m[0].w * A0223),
                                         det * -(m[0].x * A2313 - m[0].z * A0313 + m[0].w * A0213),
                                         det * (m[0].x * A2312 - m[0].z * A0312 + m[0].w * A0212)},
                                        {det * (m[1].x * A1323 - m[1].y * A0323 + m[1].w * A0123),
                                         det * -(m[0].x * A1323 - m[0].y * A0323 + m[0].w * A0123),
                                         det * (m[0].x * A1313 - m[0].y * A0313 + m[0].w * A0113),
                                         det * -(m[0].x * A1312 - m[0].y * A0312 + m[0].w * A0112)},
                                        {det * -(m[1].x * A1223 - m[1].y * A0223 + m[1].z * A0123),
                                         det * (m[0].x * A1223 - m[0].y * A0223 + m[0].z * A0123),
                                         det * -(m[0].x * A1213 - m[0].y * A0213 + m[0].z * A0113),
                                         det * (m[0].x * A1212 - m[0].y * A0212 + m[0].z * A0112)});
    }
  }
}